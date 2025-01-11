#include<fcntl.h>
#include<iostream>
#include<arpa/inet.h>
#include<sys/epoll.h>
#include<sys/stat.h>
#include<string.h>
#include<unistd.h>

#define MAXSIZE 2048

using namespace std;

//获取一行\r\n结尾的数据，符合http报文格式
int get_line(int cfd,char* buf,int size)
{
    char c=0;
    int n,i=0;
    while(i<size-1&&c!='\n')
    {
        n=recv(cfd,&c,1,0);
        if(n>0)
        {
            if(c=='/r')
            {
                n=recv(cfd,&c,1,MSG_PEEK);  //模拟读一次
                if(n>0&&c=='\n')
                    recv(cfd,&c,1,0);
                else
                    c='\n';
            }
            buf[i]=c;
            i++;
        }
        else c='\n';
    }
    buf[i]=0;
    if(n==-1) i=n;
    return i;
}

int init_listen_fd(int port,int epfd)
{
    int lfd=socket(AF_INET,SOCK_STREAM,0);
    sockaddr_in serv;
    serv.sin_family=AF_INET;
    serv.sin_port=htons(port);
    serv.sin_addr.s_addr=htonl(INADDR_ANY);
    int opt=1;
    setsockopt(lfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));   //端口复用
    bind(lfd,(sockaddr*)&serv,sizeof(serv));
    listen(lfd,128);
    epoll_event ev;
    ev.events=EPOLLIN;
    ev.data.fd=lfd;
    epoll_ctl(epfd,EPOLL_CTL_ADD,lfd,&ev);
    return lfd;
}

void do_accept(int lfd,int epfd)
{
    sockaddr_in cli;
    socklen_t cli_len=sizeof(cli);
    int cfd=accept(lfd,(sockaddr*)&cli,&cli_len);
    if(cfd==-1)
    {
        perror("accept error");
        exit(1);
    }
    char cli_ip[64]={0};
    cout<<"New Client IP: "<<inet_ntop(AF_INET,&cli.sin_addr.s_addr,cli_ip,sizeof(cli_ip))<<
    ",Port: "<<ntohs(cli.sin_port)<<",cfd= "<<cfd<<endl;    //打印客户端IP和Port
    int flag=fcntl(cfd,F_GETFL);    //设置cfd非阻塞
    flag|=O_NONBLOCK;
    fcntl(cfd,F_SETFL,flag);
    epoll_event ev;
    ev.data.fd=cfd;
    ev.events=EPOLLIN|EPOLLET;
    epoll_ctl(epfd,EPOLL_CTL_ADD,cfd,&ev);
}

//关闭连接
void disconnected(int cfd,int epfd)
{
    int ret=epoll_ctl(epfd,EPOLL_CTL_DEL,cfd,NULL);
    if(ret!=0)
    {
        perror("epoll_ctl error");
        exit(1);
    }
    close(cfd);
}

//发送http回应
void send_response(int cfd,int no,const char* disp,const char* type,int len)
{   
    char buf[1024]={0};
    sprintf(buf,"HTTP/1.1 %d %s\r\n",no,disp);
    sprintf(buf+strlen(buf),"%s\r\n",type);
    sprintf(buf+strlen(buf),"Content-Length:%d\r\n",len);
    sprintf(buf+strlen(buf),"\r\n");
    send(cfd,buf,strlen(buf),0);
}

//发送服务器本地文件
void send_file(int cfd,const char* file)
{
    int fd=open(file,O_RDONLY);
    if(fd==-1)
    {
        send_file(cfd,"404.html");
        perror("open file error");
    }
    int n=0;
    char buf[1024]={0};
    while(n=read(fd,buf,sizeof(buf)))
        send(cfd,buf,n,0);
    close(fd);
}

const char* get_file_type(const char* name)
{
    const char* dot=strrchr(name,'.');  //自右向左查找.;
    if(dot==NULL) return "Content-Type: text/plain; charset=utf-8";
    if(!strcmp(dot,".html")||!strcmp(dot,".htm")) return "Content-Type: text/html; charset=utf-8";
    if(!strcmp(dot,".jpg")||!strcmp(dot,".jpeg")) return "Content-Type: image/jpeg";
    if(!strcmp(dot,".gif")) return "Content-Type: image/gif";
    if(!strcmp(dot,".png")) return "Content-Type: image/png";
    if(!strcmp(dot,".css")) return "Content-Type: text/css";
    if(!strcmp(dot,".au")) return "Content-Type: audio/basic";
    if(!strcmp(dot,".wav")) return "Content-Type: audio/wav";
    if(!strcmp(dot,".avi")) return "Content-Type: video/quicktime";
    if(!strcmp(dot,".mov")||!strcmp(dot,".qt")) return "Content-Type: video/x-msvideo";
    if(!strcmp(dot,".mpeg")||!strcmp(dot,".mpe")) return "Content-Type: video/mpeg";
    if(!strcmp(dot,".vrml")||!strcmp(dot,".wrl")) return "Content-Type: model/vrml";
    if(!strcmp(dot,".midi")||!strcmp(dot,".mid")) return "Content-Type: audio/midi";
    if(!strcmp(dot,".mp3")) return "Content-Type: audio/mp3";
    if(!strcmp(dot,".ogg")) return "Content-Type: application/ogg";
    if(!strcmp(dot,".pdf")) return "Content-Type: application/pdf";
    if(!strcmp(dot,".pac")) return "Content-Type: application/x-ns-proxy-autoconfig";
    return "Content-Type: text/plain; charset=utf-8";
}

//处理http请求，判断文件是否存在，回发
void http_request(int cfd,const char* file)
{
    struct stat sbuf;
    int ret=stat(file,&sbuf);
    if(ret!=0)
    {
        send_response(cfd,200,"OK",get_file_type("404.html"),-1);
        send_file(cfd,"404.html");
        perror("stat error");
    }
    if(S_ISREG(sbuf.st_mode))   //普通文件
    {
        cout<<"----------is file"<<endl;
        send_response(cfd,200,"OK",get_file_type(file),-1);
        send_file(cfd,file);
    }
}

void do_read(int cfd,int epfd)
{
    //读取一行http报文，拆分，获取get、文件名、协议号
    char line[1024]={0};
    int len=get_line(cfd,line,sizeof(line));
    if(len==0)
    {
        cout<<"Server checked cilent closed..."<<endl;
        disconnected(cfd,epfd);
    }
    else
    {
        char method[16],path[256],protocol[16];
        sscanf(line,"%[^ ] %[^ ] %[^ ]",method,path,protocol);  //正则表达式获取文件名
        cout<<"method = "<<method<<",path = "<<path<<",protocol = "<<protocol;
        while(1)
        {
            char buf[1024];
            len=get_line(cfd,buf,sizeof(buf));
            if(len==0) break;
            else if(len==-1) break;
        }
        if(strncasecmp(method,"GET",3)==0)
        {
            char* file=path+1;  //取出客户端要访问的文件名
            http_request(cfd,file);
        }
    }
        
}

void epoll_run(int port)
{
    epoll_event all_events[MAXSIZE];
    int epfd=epoll_create(MAXSIZE);
    if(epfd==-1)
    {
        perror("epoll_create error");
        exit(10);
    }
    int lfd=init_listen_fd(port,epfd);
    while(1)
    {
        int ret=epoll_wait(epfd,all_events,MAXSIZE,-1);
        if(ret==-1)
        {
            perror("epoll_wait error");
            exit(1);
        }
        for(int i=0;i<ret;i++)
        {
            epoll_event* pev=&all_events[i];
            if(!(pev->events&EPOLLIN))
                continue;
            if(pev->data.fd==lfd)
                do_accept(lfd,epfd);
            else
                do_read(pev->data.fd,epfd);
        }
    }
}

int main(int argc,char *argv[])
{
    if(argc<3) cout<<"./a.out port path"<<endl;
    argv[1]="9876";
    argv[2]="/home/amor568/桌面/cpp/网络编程/http/dir";
    int port=atoi(argv[1]);
    int ret=chdir(argv[2]); //改变进程的工作目录
    if(ret!=0)
    {
        perror("chdir error");
        exit(1);
    }
    epoll_run(port);
    return 0;
}
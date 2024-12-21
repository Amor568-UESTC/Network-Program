#include<iostream>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<errno.h>
#include<ctype.h>  
#include<fcntl.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/epoll.h>
#include"wrap.h"

using namespace std;

#define MAX_EVENTS 1024
#define SER_PORT 8080
#define BUF_LEN 4096

void senddata(int fd,int events,void* arg);

struct myevent_s
{
    int fd; //描述符
    int events; //监听事件
    void* arg;  //泛型参数
    void(*call_back)(int fd,int events,void* arg);  //回调函数
    int status; //是否在监听：1在树上，0不在
    char buf[BUF_LEN];
    int len;
    long last_active;   //记录每次加入时间
};

int g_efd;  //epoll红黑树
struct myevent_s g_events[MAX_EVENTS+1];


void eventset(struct myevent_s* ev,int fd,void(*call_back)(int,int,void*),void* arg)
{
    ev->fd=fd;
    ev->call_back=call_back;
    ev->events=0;
    ev->status=0;
    memset(ev->buf,0,sizeof(ev->buf));
    ev->len=0;
    ev->last_active=time(NULL);
    return;
}

void eventadd(int efd,int events,struct myevent_s* ev)
{
    struct epoll_event epv={0,{0}};
    int op;
    epv.data.ptr=ev;
    epv.events=ev->events=events;

    if(ev->status==0)
    {
        op=EPOLL_CTL_ADD;
        ev->status=1;
    }

    if(epoll_ctl(efd,op,ev->fd,&epv)<0)
        cout<<"event add failed [fd="<<ev->fd<<"], event["
        <<events<<"]"<<endl;
    else
        cout<<"event add OK [fd="<<ev->fd<<"], op="<<op<<
        ", events["<<events<<"]"<<endl;
    return ;
}

void eventdel(int efd,struct myevent_s* ev)
{
    struct epoll_event epv={0,{0}};
    if(ev->status!=1)
        return ;
    epv.data.ptr=NULL;
    ev->status=0;
    epoll_ctl(efd,EPOLL_CTL_DEL,ev->fd,&epv);
    return ;
}

void recvdata(int fd,int events,void* arg)
{
    struct myevent_s* ev=(struct myevent_s*)arg;
    int len;
    len=recv(fd,ev->buf,sizeof(ev->buf),0); //同read
    eventdel(g_efd,ev);
    if(len>0)
    {
        ev->len=len;
        ev->buf[len]='\0';  //字符串结束
        cout<<"C["<<fd<<"]:"<<ev->buf<<endl;
        eventset(ev,fd,senddata,ev);    //回调函数senddata
        eventadd(g_efd,EPOLLOUT,ev);   //fd加入红黑树监听写事件
    }
    else ;//不愿意写了
    return ;
}

void senddata(int fd,int events,void* arg)
{
    struct myevent_s* ev=(struct myevent_s*)arg;
    int len;
    len=send(fd,ev->buf,ev->len,0); //写给客户端
    eventdel(g_efd,ev);
    if(len>0)
    {
        cout<<"send[fd="<<fd<<"],["<<len<<"]"<<ev->buf<<endl;
        eventset(ev,fd,recvdata,ev);    //回调改为recvdata
        eventadd(g_efd,EPOLLIN,ev);     //fd加红黑树监听读事件 
    }
    return ;
}

//与客户端建立连接
void acceptconn(int lfd,int events,void* arg)
{
    struct sockaddr_in c;   //client addr
    socklen_t len=sizeof(c);
    int cfd,i;
    cfd=Accept(lfd,(struct sockaddr*)&c,&len);
    do
    {
        for(i=0;i<MAX_EVENTS;i++)
            if(g_events[i].status==0)
                break;
        if(i==MAX_EVENTS)
            cout<<__func__<<": max connect limit["<<MAX_EVENTS
            <<"]"<<endl;
        
        int flag=0;
        if((flag=fcntl(cfd,F_SETFL,O_NONBLOCK))<0)
        {
            cout<<__func__<<": fcntl nonblocking failed,"
            <<strerror(errno);
            break;
        }

        //cfd设置一个myevent_s结构体，回调函数设置为recvdata
        eventset(&g_events[i],cfd,recvdata,&g_events[i]);
        eventadd(g_efd,EPOLLIN,&g_events[i]);
        //cfd添加到红黑树中监听读事件
    } while (0);

    cout<<"new connect ["<<inet_ntoa(c.sin_addr)<<":"<<
    ntohs(c.sin_port)<<"][time:"<<g_events[i].last_active
    <<"],pos["<<i<<"]"<<endl;

    return ;
}

void initlistensocket(int efd,unsigned short port)
{
    struct sockaddr_in sin;
    int lfd=socket(AF_INET,SOCK_STREAM,0);
    fcntl(lfd,F_SETFL,O_NONBLOCK);  //设置非阻塞

    memset(&sin,0,sizeof(sin));
    sin.sin_family=AF_INET;
    sin.sin_addr.s_addr=INADDR_ANY;
    sin.sin_port=htons(port);

    Bind(lfd,(struct sockaddr*)&sin,sizeof(sin));
    Listen(lfd,20);

    eventset(&g_events[MAX_EVENTS],lfd,acceptconn,&g_events[MAX_EVENTS]);

    eventadd(efd,EPOLLIN,&g_events[MAX_EVENTS]);
    return ;
}

int main(int argc,char* argv[])
{
    unsigned short port=SER_PORT;
    if(argc==2)
        port=atoi(argv[1]); //指定端口
    
    g_efd=epoll_create(MAX_EVENTS+1);
    if(g_efd<0)
        cout<<"create efd in "<<__func__<<" err "
        <<strerror(errno)<<endl;

    initlistensocket(g_efd,port); //初始化监听socket

    struct epoll_event events[MAX_EVENTS+1];
    cout<<"server running:port["<<port<<"]"<<endl;

    int checkpos=0,i;
    while(1)
    {
        long now=time(NULL);    //当前时间
        for(i=0;i<100;i++,checkpos++)   //一次检测100个，60s
        {
            if(checkpos==MAX_EVENTS)
                checkpos=0;
            if(g_events[checkpos].status!=1)
                continue;
            
            long duration=now-g_events[checkpos].last_active;

            if(duration>=60)
            {
                close(g_events[checkpos].fd);
                cout<<"[fd="<<g_events[checkpos].fd<<"] timeout"<<endl;
                eventdel(g_efd,&g_events[checkpos]); //移除客户端
            }

        }
        //监听红黑树将满足的事件添加到events中，1s
        int nfd=epoll_wait(g_efd,events,MAX_EVENTS+1,1000);
        if(nfd<0)
        {
            cout<<"epoll_wait error, exit"<<endl;
            break;
        }
        for(i=0;i<nfd;i++)
        {
            //使用自定义结构体接收联合体data的void* ptr成员
            struct myevent_s* ev=(struct myevent_s*)events[i].data.ptr;
            if((events[i].events&EPOLLIN)&&(ev->events&EPOLLIN))    //读就绪事件
                ev->call_back(ev->fd,events[i].events,ev->arg);
            if((events[i].events&EPOLLOUT)&&(ev->events&EPOLLOUT))  //写就绪事件
                ev->call_back(ev->fd,events[i].events,ev->arg);
        }

    }
    return 0;
}
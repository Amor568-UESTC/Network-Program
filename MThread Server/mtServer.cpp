#include<iostream>
#include<unistd.h>
#include<errno.h>
#include<signal.h>
#include<pthread.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<strings.h>
#include<sys/wait.h>
#include<ctype.h>
#include<fcntl.h>
#include"wrap.h"

#define SRV_PORT 9999
#define MAXLINE 8192

struct s_info
{
    struct sockaddr_in cliaddr;
    int connfd;
};

void *do_work(void* arg)
{
    struct s_info *ts=(struct s_info*)arg;
    char buf[MAXLINE];
    char str[INET_ADDRSTRLEN];  //16

    while(1)
    {
        int n=Read(ts->connfd,buf,MAXLINE);
        if(n==0)
        {
            std::cout<<"the client "<<ts->connfd<<" closed..."<<std::endl;
            break;
        }

        std::cout<<"received from "<<inet_ntop(AF_INET,&(*ts).cliaddr.sin_addr,str,sizeof(str))
        <<" at PORT "<<ntohs((*ts).cliaddr.sin_port);

        for(int i=0;i<n;i++)
            buf[i]=toupper(buf[i]);
            
        Write(STDOUT_FILENO,buf,n);
        Write(ts->connfd,buf,n);
    }   
    Close(ts->connfd);
}

int main()
{
    int lfd,cfd;
    struct sockaddr_in srv_addr,clt_addr;
    pthread_t tid;
    struct s_info ts[256];
    socklen_t clt_addr_len=sizeof(clt_addr);
    //memset(&srv_addr,0,sizeof(srv_addr));
    bzero(&srv_addr,sizeof(srv_addr));
    //地址结构清零
    srv_addr.sin_family=AF_INET;
    srv_addr.sin_port=htons(SRV_PORT);
    srv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    lfd=Socket(AF_INET,SOCK_STREAM,0);
    Bind(lfd,(struct sockaddr*)&srv_addr,sizeof(srv_addr));
    Listen(lfd,128);
    std::cout<<"Accepting client connect..."<<std::endl;
    for(int i=0;;i++)
    {
        cfd=Accept(lfd,(struct sockaddr*)&clt_addr,&clt_addr_len);
        ts[i].cliaddr=clt_addr;
        ts[i].connfd=cfd;

        pthread_create(&tid,NULL,do_work,(void*)&ts[i]);
        pthread_detach(tid);
    }
    return 0;
}
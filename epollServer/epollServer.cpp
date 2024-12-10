#include<iostream>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<ctype.h>  
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/epoll.h>
#include"wrap.h"

using namespace std;

#define MAXLINE 8192
#define SER_PORT 8000
#define OPEN_MAX 5000

int main()
{
    int i,lfd,cfd,sockfd;
    int n,num=0;
    ssize_t nready,efd,res;
    char buf[MAXLINE],str[INET_ADDRSTRLEN];
    struct sockaddr_in cliaddr,seraddr;
    socklen_t clilen=sizeof(cliaddr);
    struct epoll_event tmpep,ep[OPEN_MAX];

    lfd=Socket(AF_INET,SOCK_STREAM,0);
    int opt=1;
    setsockopt(lfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
    seraddr.sin_family=AF_INET;
    seraddr.sin_addr.s_addr=htonl(INADDR_ANY);
    seraddr.sin_port=htons(SER_PORT);

    Bind(lfd,(sockaddr*)&seraddr,sizeof(seraddr));
    Listen(lfd,20);

    efd=epoll_create(OPEN_MAX); //创建ep红黑树，efd指向根节点
    if(efd==-1)
        perr_exit("epoll_create error");

    tmpep.events=EPOLLIN;
    tmpep.data.fd=lfd;
    res=epoll_ctl(efd,EPOLL_CTL_ADD,lfd,&tmpep);
    //将lfd放入红黑树
    if(res==-1)
        perr_exit("epoll_ctl error");

    while(1)
    {
        nready=epoll_wait(efd,ep,OPEN_MAX,-1);
        //阻塞监听，-1表示永久阻塞
        if(nready==-1)
            perr_exit("epoll_wait error");
        
        for(i=0;i<nready;i++)
        {
            if(!(ep[i].events&EPOLLIN)) //不为读事件
                continue;
            if(ep[i].data.fd==lfd)
            {
                cfd=Accept(lfd,(sockaddr*)&cliaddr,&clilen);
                cout<<"receive from "<<inet_ntop(AF_INET,&cliaddr.sin_addr,str,sizeof(str))
                <<" at port "<<ntohs(cliaddr.sin_port)<<endl;
                cout<<"cfd "<<cfd<<"---client "<<++num<<endl;
                tmpep.events=EPOLLIN;
                tmpep.data.fd=cfd;
                res=epoll_ctl(efd,EPOLL_CTL_ADD,cfd,&tmpep);
                if(res==-1)
                    perr_exit("epoll_ctl error");
            }
            else
            {
                sockfd=ep[i].data.fd;
                n=Read(sockfd,buf,MAXLINE);
                if(n==0)
                {
                    res=epoll_ctl(efd,EPOLL_CTL_DEL,sockfd,NULL);
                    //在树中删除节点
                    if(res==-1)
                        perr_exit("epoll_ctl error");
                    Close(sockfd);
                    cout<<"client["<<sockfd<<"] closed connection"<<endl;
                }
                else if(n<0)
                {
                    perror("read n < 0 error: ");
                    res=epoll_ctl(efd,EPOLL_CTL_DEL,sockfd,NULL);
                    Close(sockfd);
                }
                else
                {
                    for(i=0;i<n;i++)
                        buf[i]=toupper(buf[i]);
                    Write(STDOUT_FILENO,buf,n);
                    Write(sockfd,buf,n);
                }
            }
        }
    }
    Close(lfd);

    return 0;
}
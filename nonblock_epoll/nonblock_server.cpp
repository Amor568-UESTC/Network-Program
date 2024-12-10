#include<unistd.h>
#include<iostream>
#include<arpa/inet.h>
#include<sys/epoll.h>
#include<sys/socket.h>
#include<string.h>
#include<fcntl.h>
using namespace std;

#define SER_PORT 9000
#define MAXLINE 10
int main()
{
    int lfd,cfd,sockfd;
    char buf[MAXLINE],str[INET_ADDRSTRLEN];
    int efd;
    int flag;
    struct sockaddr_in seraddr,cliaddr;
    socklen_t clilen=sizeof(cliaddr);
    lfd=socket(AF_INET,SOCK_STREAM,0);
    seraddr.sin_addr.s_addr=htonl(INADDR_ANY);
    seraddr.sin_port=htons(SER_PORT);
    seraddr.sin_family=AF_INET;

    bind(lfd,(sockaddr*)&seraddr,sizeof(seraddr));
    listen(lfd,128);

    struct epoll_event event;
    struct epoll_event resevent[10];
    int res,len;
    
    efd=epoll_create(10);
    event.events=EPOLLIN|EPOLLET;
    //event.events=EPOLLIN;
    cout<<"Accepting connections..."<<endl;
    cfd=accept(lfd,(sockaddr*)&cliaddr,&clilen);
    cout<<"receive from "<<inet_ntop(AF_INET,&cliaddr.sin_addr,str,sizeof(str))
    <<" at Port "<<ntohs(cliaddr.sin_port)<<endl;

    flag=fcntl(cfd,F_GETFL);    //改cfd为非阻塞读
    flag|=O_NONBLOCK;
    fcntl(cfd,F_SETFL,flag);

    event.data.fd=cfd;
    epoll_ctl(efd,EPOLL_CTL_ADD,cfd,&event);

    while(1)
    {
        cout<<"epoll_wait begin"<<endl;
        res=epoll_wait(efd,resevent,10,-1);
        cout<<"res "<<res<<endl;
        if(resevent[0].data.fd==cfd)
        {
            while((len=read(cfd,buf,MAXLINE/2))>0)
                write(STDOUT_FILENO,buf,len);
        }
    }
    return 0;
}
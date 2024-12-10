#include<iostream>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/epoll.h>
#include<string.h>
#include<unistd.h>
#define MAXLINE 10
#define SER_PORT 9000

int main()
{
    struct sockaddr_in seraddr;
    char buf[MAXLINE];
    int sockfd,i;
    char ch='a';

    sockfd=socket(AF_INET,SOCK_STREAM,0);

    seraddr.sin_family=AF_INET;
    seraddr.sin_port=htons(SER_PORT);
    inet_pton(AF_INET,"127.0.0.1",&seraddr.sin_addr);

    connect(sockfd,(sockaddr*)&seraddr,sizeof(seraddr));

    while(1)
    {
        for(i=0;i<MAXLINE/2;i++)
            buf[i]=ch;
        buf[i-1]='\n';
        ch++;
        for(i;i<MAXLINE;i++)
            buf[i]=ch;
        buf[i-1]='\n';
        ch++;
        write(sockfd,buf,sizeof(buf));
        sleep(3);
    }
    close(sockfd);
    return 0;
}
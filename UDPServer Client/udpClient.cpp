#include<string.h>
#include<stdio.h>
#include<iostream>
#include<unistd.h>
#include<arpa/inet.h>
#include<ctype.h>

#define SERV_PORT 8000

using namespace std;

int main()
{
    sockaddr_in serv_addr;
    int sockfd;
    char buf[BUFSIZ];
    int n;
    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    bzero(&serv_addr,sizeof(serv_addr));
    inet_pton(AF_INET,"127.0.0.1",&serv_addr.sin_addr);
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(SERV_PORT);


    while(fgets(buf,BUFSIZ,stdin)!=NULL)
    {
        n=sendto(sockfd,buf,strlen(buf),0,(sockaddr*)&serv_addr,sizeof(serv_addr));
        if(n==-1) perror("sendto error");

        n=recvfrom(sockfd,buf,BUFSIZ,0,NULL,0); //NULL:不关心对端信息
        if(n==-1) perror("recvfrom error");

        write(STDOUT_FILENO,buf,n);
    }
    close(sockfd);
    return 0;
}
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
    sockaddr_in serv_addr,cli_addr;
    socklen_t cli_addr_len=sizeof(cli_addr);
    int sockfd;
    char buf[BUFSIZ];
    char str[INET_ADDRSTRLEN];
    int n;
    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    bzero(&serv_addr,sizeof(serv_addr));
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(SERV_PORT);

    bind(sockfd,(sockaddr*)&serv_addr,sizeof(serv_addr));

    cout<<"Accepting connection..."<<endl;

    while(1)
    {
        n=recvfrom(sockfd,buf,BUFSIZ,0,(sockaddr*)&cli_addr,&cli_addr_len);
        if(n==-1) perror("recvfrom error");
        cout<<"received from "<<inet_ntop(AF_INET,&cli_addr.sin_addr,str,sizeof(str))
        <<" at PORT"<<ntohs(cli_addr.sin_port)<<endl;

        for(int i=0;i<n;i++)
            buf[i]=toupper(buf[i]);

        n=sendto(sockfd,buf,n,0,(sockaddr*)&cli_addr,sizeof(cli_addr));
        if(n==-1) perror("sendto error");
    }
    close(sockfd);
    return 0;
}
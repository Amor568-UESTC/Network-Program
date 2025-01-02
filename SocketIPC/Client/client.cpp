#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<strings.h>
#include<string.h>
#include<ctype.h>
#include<arpa/inet.h>
#include<sys/un.h>
#include<stddef.h>
#include"wrap.h"

#define SERV_ADDR "serv.socket"
#define CLI_ADDR "cli.socket"

int main()
{
    int cfd,len;
    sockaddr_un servaddr,cliaddr;
    char buf[4096];

    cfd=Socket(AF_UNIX,SOCK_STREAM,0);
    bzero(&cliaddr,sizeof(cliaddr));
    cliaddr.sun_family=AF_UNIX;
    strcpy(cliaddr.sun_path,CLI_ADDR);

    len=offsetof(sockaddr_un,sun_path)+strlen(cliaddr.sun_path); //客户端地址结构有效长度

    unlink(CLI_ADDR);
    Bind(cfd,(sockaddr*)&cliaddr,len);
    
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sun_family=AF_UNIX;
    strcpy(servaddr.sun_path,SERV_ADDR);

    len=offsetof(sockaddr_un,sun_path)+strlen(servaddr.sun_path);

    Connect(cfd,(sockaddr*)&servaddr,len);

    while(fgets(buf,sizeof(buf),stdin)!=NULL)
    {
        Write(cfd,buf,strlen(buf));
        len=Read(cfd,buf,sizeof(buf));
        Write(STDOUT_FILENO,buf,len);
    }
    close(cfd);
    return 0;
}
#include<iostream>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<ctype.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<ctype.h>
#include"wrap.h"

using namespace std;

#define SERV_ADDR "serv.socket"

int main()
{
    int lfd,cfd,len,size;
    sockaddr_un servaddr,cliaddr;
    char buf[4096];

    lfd=Socket(AF_UNIX,SOCK_STREAM,0);
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sun_family=AF_UNIX;
    strcpy(servaddr.sun_path,SERV_ADDR);

    len=offsetof(sockaddr_un,sun_path)+strlen(servaddr.sun_path);   //servaddr总长度
    //offsetof为求偏移量
    unlink(SERV_ADDR);      //确保bind之前serv.sock不存在，bind会创建该文件
    Bind(lfd,(sockaddr*)&servaddr,len); //参数3不能为sizeof
    Listen(lfd,20);
    cout<<"Accepting ..."<<endl;

    while(1)
    {
        len=sizeof(cliaddr);
        cfd=Accept(lfd,(sockaddr*)&cliaddr,(socklen_t*)&len);
        len-=offsetof(sockaddr_un,sun_path);
        cliaddr.sun_path[len]=0;
        cout<<"client bind filename "<<cliaddr.sun_path<<endl;

        while((size=Read(cfd,buf,sizeof(buf)))>0)
        {
            for(int i=0;i<size;i++)
                buf[i]=toupper(buf[i]);
            write(cfd,buf,size);
        }
        close(cfd);
    }
    close(lfd);
    return 0;
}
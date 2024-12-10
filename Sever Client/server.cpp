#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<errno.h>
#include"wrap.h"

#define SERV_PORT 9527

int main()
{
    int lfd=0,cfd=0;
    char client_IP[1024],buf[BUFSIZ];;
    struct sockaddr_in serv_addr,clit_addr;
    socklen_t clit_addr_len=sizeof(clit_addr);
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(SERV_PORT);
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);

    lfd=Socket(AF_INET,SOCK_STREAM,0);
    
    Bind(lfd,(sockaddr*)&serv_addr,sizeof(serv_addr));
    
    Listen(lfd,128);

    cfd=Accept(lfd,(sockaddr*)&clit_addr_len,&clit_addr_len);

    std::cout<<"client ip:"<<inet_ntop(AF_INET,&clit_addr.sin_addr.s_addr,client_IP,sizeof(client_IP))
    <<" port:"<<ntohs(clit_addr.sin_port)<<std::endl;

    while(1)
    {
        int ret=Read(cfd,buf,sizeof(buf));
        for(int i=0;i<ret;i++)
            buf[i]+='A'-'a';
        Write(cfd,buf,ret);
        if(ret==0) break;
    }
    close(lfd);
    close(cfd);

    return 0;
}
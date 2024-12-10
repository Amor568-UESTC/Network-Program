#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<vector>
#include<poll.h>
#include<ctype.h>
#include<netinet/in.h>
#include<algorithm>
#include"wrap.h"
using namespace std;
#define SER_PORT 1234
#define OPEN_MAX 1024
#define MAXLINE 80

int main()
{
    int lfd,cfd,sockfd;
    int nready; //记录满足的fd个数
    char buf[MAXLINE],str[INET_ADDRSTRLEN];
    struct pollfd client[OPEN_MAX];
    struct sockaddr_in ser_addr,cli_addr;
    socklen_t cli_addr_len=sizeof(cli_addr);

    lfd=Socket(AF_INET,SOCK_STREAM,0);
    int opt=1;
    setsockopt(lfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
    ser_addr.sin_family=AF_INET;
    ser_addr.sin_port=htons(SER_PORT);
    ser_addr.sin_addr.s_addr=htonl(INADDR_ANY);

    Bind(lfd,(sockaddr*)&ser_addr,sizeof(ser_addr));
    Listen(lfd,128);

    int maxi=0;
    for(auto& c:client)
        c.fd=-1;
    client[0].fd=lfd;
    client[0].events=POLLIN;

    while(1)
    {
        nready=poll(client,maxi+1,-1);
        if(client[0].revents&POLLIN)
        {
            cfd=Accept(lfd,(sockaddr*)&cli_addr,&cli_addr_len);
            cout<<"receive from "<<inet_ntop(AF_INET,&cli_addr.sin_addr,str,sizeof(str))
            <<" at PORT "<<ntohs(cli_addr.sin_port)<<endl;
            int i;
            for(i=1;i<OPEN_MAX;i++)
                if(client[i].fd<0)  //找空余位置
                {
                    client[i].fd=cfd;
                    break;
                }
            if(i==OPEN_MAX) //到达最大
                perr_exit("too many clients");

            client[i].events=POLLIN;    //设置
            maxi=max(maxi,i);
            if(--nready==0)
                continue;
        }
        for(int i=1;i<=maxi;i++)
        {
            if((sockfd=client[i].fd)<0)
                continue;
            if(client[i].revents&POLLIN)
            {
                int n=Read(sockfd,buf,MAXLINE);
                if(n<0)
                {
                    if(errno==ECONNRESET)   //受到RST标志
                    {
                        cout<<"client["<<i<<"] aborted connection"<<endl;
                        Close(sockfd);
                        client[i].fd=-1;
                    }
                    else perr_exit("read error");
                }
                else if(n==0)
                {
                    cout<<"client["<<i<<"] aborted connection"<<endl;
                    Close(sockfd);
                    client[i].fd=-1;
                }
                else
                {
                    for(int j=0;j<n;j++)
                        buf[j]=toupper(buf[j]);
                    Writen(sockfd,buf,n);
                    Writen(STDOUT_FILENO,buf,n);
                }
                if(--nready==0)
                    break;
            }
        }
        
    }
    return 0;
}
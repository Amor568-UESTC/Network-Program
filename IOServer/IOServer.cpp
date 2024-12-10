#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<errno.h>
#include<ctype.h>
#include<stdlib.h>
#include<strings.h>
#include<iostream>
#include"wrap.h"
#include<math.h>

#define SRV_PORT 9999

using namespace std;

int main()
{
    int nready,client[FD_SETSIZE]; //自定义数组防止遍历1024
    int maxfd=0;
    int lfd,cfd,sockfd;
    char buf[BUFSIZ],str[INET_ADDRSTRLEN];
    struct sockaddr_in srv_addr,clt_addr;
    socklen_t clt_addr_len=sizeof(clt_addr);
    lfd=Socket(AF_INET,SOCK_STREAM,0);
    int opt=1;
    setsockopt(lfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
    bzero(&srv_addr,sizeof(srv_addr));
    srv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    srv_addr.sin_family=AF_INET;
    srv_addr.sin_port=htons(SRV_PORT);

    Bind(lfd,(struct sockaddr*)&srv_addr,sizeof(srv_addr));
    Listen(lfd,128);

    maxfd=lfd;
    int maxi=-1;    //将用作client下标
    for(int i=0;i<FD_SETSIZE;i++)
        client[i]=-1;

    fd_set rset,allset; //读集合和备份集合

    FD_ZERO(&allset);   //清空
    FD_SET(lfd,&allset);    //添加

    while(1)
    {
        rset=allset;    //备份
        nready=select(maxfd+1,&rset,NULL,NULL,NULL);
        if(nready<0)
            perr_exit("select error");
        
        if(FD_ISSET(lfd,&rset)) //满足监听
        {
            cfd=Accept(lfd,(struct sockaddr*)&clt_addr,&clt_addr_len);
            //建立连接，非阻塞  
            cout<<"received from "<<inet_ntop(AF_INET,&clt_addr.sin_addr,str,sizeof(str))
            <<" at port "<<ntohs(clt_addr.sin_port)<<endl;
            
            int i=0;
            for(i=0;i<FD_SETSIZE;i++)
                if(client[i]<0)
                {
                    client[i]=cfd;
                    break;
                }

            if(i==FD_SETSIZE)   //防止越界
                exit(1);


            FD_SET(cfd,&allset);

            maxfd=max(maxfd,cfd);
            maxi=max(maxi,i);
            //把监听数组中最大下标计入
            if(0==--nready) //是否只有监听
                continue;
        }
        for(int i=0;i<=maxi;i++)   //在client数组中寻找读事件
        {
            if((sockfd=client[i])<0)
                continue;
            if(FD_ISSET(sockfd,&rset))
            {
                int n=read(sockfd,buf,sizeof(buf));
                if(n==0)
                {
                    Close(sockfd);
                    FD_CLR(sockfd,&rset);
                    client[i]=-1;
                }
                else if(n>0)
                {
                    for(int j=0;j<n;j++)
                        buf[j]=toupper(buf[j]);
                    Write(STDOUT_FILENO,buf,n);
                    Write(sockfd,buf,n);
                }
                if(--nready==0) break;
            }
        }
            
    }
    Close(lfd);
    return 0;
}
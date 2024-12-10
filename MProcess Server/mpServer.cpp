#include<iostream>
#include<unistd.h>
#include<errno.h>
#include<signal.h>
#include<pthread.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<strings.h>
#include<sys/wait.h>
#include<ctype.h>
#include"wrap.h"

#define SRV_PORT 6666

void catch_child(int signum)
{
    while(waitpid(0,NULL,WNOHANG)>0);
    return;
}

int main()
{
    int lfd,cfd;
    struct sockaddr_in srv_addr,clt_addr;
    int ret;
    char readbuf[BUFSIZ];
    pid_t pid;
    socklen_t clt_addr_len=sizeof(clt_addr);
    //memset(&srv_addr,0,sizeof(srv_addr));
    bzero(&srv_addr,sizeof(srv_addr));
    //地址结构清零
    srv_addr.sin_family=AF_INET;
    srv_addr.sin_port=htons(SRV_PORT);
    srv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    lfd=Socket(AF_INET,SOCK_STREAM,0);
    //端口复用
    int opt=1;
    setsockopt(lfd,SOL_SOCKET,SO_REUSEADDR,(void*)&opt,sizeof(opt));

    Bind(lfd,(struct sockaddr*)&srv_addr,sizeof(srv_addr));
    Listen(lfd,128);
    while(1)
    {
        cfd=Accept(lfd,(struct sockaddr*)&clt_addr,&clt_addr_len);
        pid=fork();
        if(pid<0)
            perr_exit("fork error");
        else if(pid==0)
        {
            close(lfd);
            break;
        }
        else
        {
            struct sigaction act;
            act.sa_handler=catch_child;
            sigemptyset(&act.sa_mask);
            act.sa_flags=0;
            if(ret!=0)
                perr_exit("sigaction error");
            ret=sigaction(SIGCHLD,&act,NULL);
            close(cfd);
            continue;
        }  
    }
    //子进程工作
    if(pid==0)
        for(;;){
            ret=Read(cfd,readbuf,sizeof(readbuf));
            if(ret==0)
            {
                close(cfd);
                exit(1);
            }    
            for(int i=0;i<ret;i++)
                readbuf[i]=toupper(readbuf[i]);
            write(cfd,readbuf,ret);
            write(STDOUT_FILENO,readbuf,ret);
        }
}
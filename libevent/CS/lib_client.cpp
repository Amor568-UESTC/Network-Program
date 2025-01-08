#include<iostream>
#include<arpa/inet.h>
#include<string.h>
#include<event2/listener.h>
#include<event2/event.h>
#include<event2/bufferevent.h>
#include<unistd.h>
using namespace std;

void read_cb(bufferevent* bev,void* arg)
{
    char buf[1024]={0};
    bufferevent_read(bev,buf,sizeof(buf));
    cout<<"client say:"<<buf;
    char *p="I'm sever,have received your data!";
    bufferevent_write(bev,p,strlen(p)+1);   //此时会调用write_cb
    sleep(1);
}

void write_cb(bufferevent* bev,void* arg)
{
    cout<<"I'm server,have written data to client.This func call back...\n";
}

void event_cb(bufferevent* bev,short events,void* arg)
{
    if(events&BEV_EVENT_EOF)
        cout<<"connection closed"<<endl;
    else if(events&BEV_EVENT_ERROR)
        cout<<"some other error"<<endl;

    bufferevent_free(bev);
    cout<<"buffevent资源已释放..."<<endl;
}

void read_terminal(evutil_socket_t fd,short events,void* arg)
{
    char buf[1024]={0};
    int len=read(fd,buf,sizeof(buf));
    bufferevent* bev=(bufferevent*)arg;
    bufferevent_write(bev,buf,len+1);
}

int main()
{
    event_base* base=event_base_new();
    int fd=socket(AF_INET,SOCK_STREAM,0);
    bufferevent* bev=bufferevent_socket_new(base,fd,BEV_OPT_CLOSE_ON_FREE);
    
    sockaddr_in serv;
    memset(&serv,0,sizeof(serv));
    serv.sin_family=AF_INET;
    serv.sin_port=htons(9876);
    inet_pton(AF_INET,"127.0.0.1",&serv.sin_addr.s_addr);

    bufferevent_socket_connect(bev,(sockaddr*)&serv,sizeof(serv));
    bufferevent_setcb(bev,read_cb,write_cb,NULL,NULL);
    //bufferevent_enable(bev,EV_READ);  //设置读回调生效
    event* ev=event_new(base,STDIN_FILENO,EV_READ|EV_PERSIST,read_terminal,bev);
    event_add(ev,NULL);
    event_base_dispatch(base);  //启动循环
    event_free(ev);
    event_base_free(base);
    return 0;
}
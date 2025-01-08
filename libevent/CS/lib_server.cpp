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
    cout<<"client say:"<<buf<<endl;
    char *p="I'm sever,have received your data!";
    bufferevent_write(bev,p,strlen(p)+1);   //此时会调用write_cb
    sleep(1);
}

void write_cb(bufferevent* bev,void* arg)
{
    cout<<"I'm server,have written data to client."<<endl;
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

void cb_listener(evconnlistener* listener,evutil_socket_t fd,sockaddr* addr,int len,void* ptr)
{
    cout<<"connect new client"<<endl;
    event_base* base=(event_base*)ptr;
    bufferevent* bev=bufferevent_socket_new(base,fd,BEV_OPT_CLOSE_ON_FREE); //添加新事件
    bufferevent_setcb(bev,read_cb,write_cb,event_cb,NULL);  //设置缓冲区的回调
    bufferevent_enable(bev,EV_READ);    //启用读缓冲（默认是disable）
}

int main()
{
    sockaddr_in serv;
    memset(&serv,0,sizeof(serv));
    serv.sin_family=AF_INET;
    serv.sin_port=htons(9876);
    serv.sin_addr.s_addr=htonl(INADDR_ANY);

    event_base* base=event_base_new();
    //监听器
    evconnlistener* listener=evconnlistener_new_bind(base,cb_listener,(void*)base,
    LEV_OPT_CLOSE_ON_FREE|LEV_OPT_REUSEABLE,-1,(sockaddr*)&serv,sizeof(serv));
    event_base_dispatch(base);  //启动循环
    evconnlistener_free(listener);  //
    event_base_free(base);
    return 0;
}
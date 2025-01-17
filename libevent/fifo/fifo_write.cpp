#include<iostream>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<fcntl.h>
#include<event2/event.h>

using namespace std;

void write_cb(evutil_socket_t fd,short what,void* arg)
{
    char buf[1024]={0};
    static int num=0;
    sprintf(buf,"hello world-%d\n",num++);
    write(fd,buf,strlen(buf)+1);
    sleep(1);
}

int main()
{
    int fd=open("myfifo",O_WRONLY|O_NONBLOCK);
    if(fd==-1)
    {
        perror("open error");
        exit(1);
    }

    event_base* base=event_base_new();
    event* ev=event_new(base,fd,EV_WRITE|EV_PERSIST,write_cb,NULL);
    event_add(ev,NULL);
    event_base_dispatch(base);
    event_free(ev);
    event_base_free(base);
    close(fd);
    
    return 0;
}
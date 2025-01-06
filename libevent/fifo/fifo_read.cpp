#include<iostream>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<fcntl.h>
#include<event2/event.h>

using namespace std;

void read_cb(evutil_socket_t fd,short what,void* arg)
{
    char buf[1024]={0};
    int len=read(fd,buf,sizeof(buf));
    if(what&EV_READ)
        cout<<"read event: Yes"<<endl;
    else cout<<"read event: No"<<endl;
    cout<<"data len = "<<len<<", buf = "<<buf;
    sleep(1);
}

int main()
{
    unlink("myfifo");
    mkfifo("myfifo",0664);
    int fd=open("myfifo",O_RDONLY|O_NONBLOCK);
    if(fd==-1)
    {
        perror("open error");
        exit(1);
    }

    event_base* base=event_base_new();
    event* ev=event_new(base,fd,EV_READ|EV_PERSIST,read_cb,NULL);
    event_add(ev,NULL);
    event_base_dispatch(base);
    event_free(ev);
    event_base_free(base);
    close(fd);
    
    return 0;
}
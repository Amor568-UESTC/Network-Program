#include<iostream>
#include<string.h>
#include<pthread.h>
#include

using namespace std;

typedef struct
{
    void*(*function)(void*);
    void* arg;
}threadpool_task_t;

struct threadpool_t
{
    pthread_mutex_t lock;   //用于锁结构体
    pthread_mutex_t thread_counter; //忙线程个数

    pthread_cond_t queue_not_full;  
    pthread_cond_t queue_not_empty;

    pthread_t *threads; //每个线程的tid
    pthread_t adjust_tid;   //管理线程tid
    threadpool_task_t *task_queue;  //任务队列

    int min_thr_num;
    int max_thr_num;
    int live_thr_num;
    int busy_thr_num;
    int wait_exit_thr_num;

    int queue_front;
    int qurue_rear;
    int queue_size;
    int queue_max_size;

    bool shoutdown; //标志位，线程池使用状态
};

void* threadpool_thread(void* threadpool);
void* adjust_thread(void* threadpool);
int is_thread_alive(pthread_t tid);
int threadpool_free(threadpool_t* pool);
void threadpool_create();
void threadpool_add();


int main()
{
    threadpool_t* thp=threadpool_create(3,100,100);
    cout<<"pool inited";

    int num[20],i;
    for(i=0;i<20;i++)
    {
        num[i]=i;
        cout<<"add task "<<i<<endl;
        threadpool_add(thp,process,(void*)&num[i]);
    }
    sleep(10);
    threadpool_destroy(thp);
    return 0;
    //今天先写到这里，练琴去了.
}
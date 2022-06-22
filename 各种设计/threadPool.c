//一个简单的线程池的实现
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>



struct task
{
    void (*taskfunc)(void*);
    void *args;
    struct  task *next;
};

#define MAX_THREAD_NUM 10;
struct threadpool
{
    //线程数
    int  threadnum;
    pthread_t tid[10];
    //访问任务队列的锁
    pthread_mutex_t mutex;
    pthread_cond_t putcond;
    pthread_cond_t getcond;
    struct task* taskqueue; //任务队列
    int maxtasknum;
    int curtasknum;
};

//线程的共有函数
//任务队列中的函数
void * routine(void* arg)
{
    struct threadpool *thrdpool = (struct threadpool*)arg;
       
    struct task* ptask;
    void (*taskfunc)(void*) ;
    void *args ;

    while(1)
    {
        //从thrdpool的工作队列中不断的取任务执行任务函数
        pthread_mutex_lock(&thrdpool->mutex);
        while(thrdpool->curtasknum == 0)
        {
            printf("Not Enough Task.....\n");
            pthread_cond_wait(&thrdpool->getcond, &thrdpool->mutex);
        }
        ptask = thrdpool->taskqueue;
        if(thrdpool->taskqueue->next)
        {
            thrdpool->taskqueue = thrdpool->taskqueue->next;
        }
        else
        {
            thrdpool->taskqueue = NULL;
        }
        ptask->next = NULL;

        pthread_mutex_unlock(&thrdpool->mutex);
        pthread_cond_signal(&thrdpool->putcond);
        thrdpool->curtasknum--;
        taskfunc = ptask->taskfunc;
        args = ptask->args;
        taskfunc(args); //执行任务
        free(ptask);
     }
}

struct threadpool* thrdpool_create(size_t threads, size_t maxtasknum)
{
    struct threadpool  *thrdpool= (struct threadpool*)malloc(sizeof(struct threadpool));
    if(thrdpool == NULL)
        return NULL;
    pthread_mutex_init(&thrdpool->mutex, NULL);
    pthread_cond_init(&thrdpool->putcond, NULL);
    pthread_cond_init(&thrdpool->getcond, NULL);
    
    thrdpool->threadnum = threads;
    thrdpool->curtasknum =0;
    thrdpool->maxtasknum  =maxtasknum;
    thrdpool->taskqueue = NULL;

    for(int i = 0; i < threads;++i)
    {
         pthread_create(&thrdpool->tid[i], NULL, routine, thrdpool);
    }
    return thrdpool;
}

void thrdpool_schedule(struct threadpool*thrdpool, struct task *ptask)
{
    pthread_mutex_lock(&thrdpool->mutex);
    while(thrdpool->maxtasknum == thrdpool->curtasknum) //满了不能再向队列中放任务了
    {
        printf("pool task full can't add more task........\n");
        pthread_cond_wait(&thrdpool->putcond, &thrdpool->mutex);//阻塞当前线程
    }
    if(thrdpool->taskqueue)
    {
        ptask->next = thrdpool->taskqueue->next;
        thrdpool->taskqueue->next = ptask;
    }
    else
    {
        thrdpool->taskqueue = ptask;
    }
    printf("add one task success\n");
    thrdpool->curtasknum++;
    pthread_mutex_unlock(&thrdpool->mutex);
    pthread_cond_broadcast(&thrdpool->getcond);  //唤醒被getcond阻塞的线程
}

void thrdpool_joinall(struct threadpool*  thrdpool)
{
     for(int i = 0; i < thrdpool->threadnum; ++i)
    {
         pthread_join(thrdpool->tid[i], NULL);
    }
    
}
void taskfunc(void* arg)
{
    int a = *(int*)arg;
    printf("doing task......tasknumber:%d\n",a);
}

int main()
{ 
    struct threadpool*  thrdpool  = thrdpool_create(3 , 10) ;
    while(1)
    {
        for (int i = 0; i < 10; ++i)
        {
            sleep(1);
            struct task* ptask1 = (struct task*)malloc(sizeof(struct task));
            ptask1->taskfunc = taskfunc;
            ptask1->args =(void*)&i;
            thrdpool_schedule(thrdpool, ptask1);
        }
    }
    thrdpool_joinall(thrdpool);
    return 0;
}

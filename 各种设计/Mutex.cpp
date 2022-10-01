#include<pthread.h>
#include<stdio.h>
#include <unistd.h>
#include <queue>
#include <stdlib.h>

class Mutex
{
public:
    Mutex()
    {
        pthread_mutex_init(&mutex_ ,NULL);
    }
    ~Mutex()
    {
        pthread_mutex_destroy(&mutex_);
    }
    pthread_mutex_t * getPthreadMutex()
    {
        return &mutex_;
    }
   void Lock()
    {
        pthread_mutex_lock(&mutex_);
    }

   void Unlock()
    {
        pthread_mutex_unlock(&mutex_);
    }

private:
    pthread_mutex_t mutex_;
};
//RAII 单独使用锁的时候
class MutexGuard
{
public:
    MutexGuard(Mutex&mutex):mutex_(mutex)
    {
        mutex_.Lock();
    }
    ~MutexGuard()
    {
        mutex_.Unlock();
    }
private:
    Mutex &mutex_;
};
//锁+条件变量
class Condition
{
public:
    Condition(Mutex&mutex):mutex_(mutex){
        pthread_cond_init(&pcond, NULL);
    }
    ~Condition()
    {
        pthread_cond_destroy(&pcond);
    }

    void wait()
    {
        pthread_cond_wait(&pcond, mutex_.getPthreadMutex());
    }
    void nofify()
    {
        pthread_cond_signal(&pcond);
    }
    void notifyall()
    {
        pthread_cond_broadcast(&pcond);
    }
private:
    Mutex &mutex_;
    pthread_cond_t pcond;

};

#if 0
class Task
{
    public:
    int taskno;
    Task(int i):taskno(i){}
    void run()
    {
        printf("task :%d  is doing ....\n", taskno);
    }
};


class BlockTaskQueue
{ 
private:
    Condition Cond(mutex1);
    Mutex mutex1;
    std::queue<Task> blockTaskQueue;
public:
    void *proFunc(void*arg)
    {
        while(1)
        {
            int sleeptm = rand()%5;
            sleep(sleeptm);
            int taskno = *(int*)arg;
            printf("add task:%d to taskqueue....\n", taskno);
            Task task(taskno);
            blockTaskQueue.push(task);
            Cond.notifyall();
        }
    }
    void *conFunc(void* arg)
    {
        while(blockTaskQueue.empty())
        {
            printf("waiting for task...\n");
            Cond.wait();
        }
        Task &tsk = blockTaskQueue.front();
        tsk.run();
        blockTaskQueue.pop();
    }
};
#endif


class threadSafeAdd 
{
public:
    threadSafeAdd():gCount(0){}
    Mutex mutex;
    void AddCount()
    {
        MutexGuard Mtg(mutex);
        gCount++;
    }
    int getCount()
    {
        return gCount;
    }
private:
    int gCount;
};

void *threadFunc(void* arg)
{
    threadSafeAdd &thsafeadd = *(threadSafeAdd*)arg;
    thsafeadd.AddCount();
}

int main(int argc, char * argv[])
{
    if(argc < 4)
    {
        printf("usage:%s add pro con \n",argv[0]);
        return -1;
    }
    int ADDCOUNT = atoi(argv[1]);
    int PROCOUNT = atoi(argv[2]);
    int CONCOUNT = atoi(argv[3]);

    threadSafeAdd thad;

    pthread_t tid[ADDCOUNT];
    for(int i = 0 ; i < ADDCOUNT ; ++i)
        pthread_create(&tid[i], NULL, threadFunc, &thad);

    printf("Now Count is :%d\n", thad.getCount());


    
    for (int i = 0 ; i < ADDCOUNT ; ++i)
        pthread_join(tid[i] , NULL);
    printf("Now Count is :%d\n", thad.getCount());
#if 0
    pthread_t tidcond[CONCOUNT];
    int taskno[CONCOUNT];
    for ( int i = 0 ; i < CONCOUNT ;++i)
    {
        taskno[i] = i;
        pthread_create(&tidcond[i], NULL, proFunc, &taskno[i]);
    }
    for (int i = 0 ; i < CONCOUNT;++i)
    {
        pthread_join(tidcond[i], NULL);
    }


    pthread_t tidpro[PROCOUNT];
    for ( int i = 0 ; i < PROCOUNT ; ++i)
    {
        pthread_create(&tidpro[i], NULL, conFunc, NULL);
    }
    for (int i = 0 ; i < PROCOUNT ;++i)
    {
        pthread_join(tidpro[i], NULL);
    }
#endif
    
}

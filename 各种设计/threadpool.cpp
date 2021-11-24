#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <list>
#include <cstdio>
#include <exception>
#include <pthread.h>
#include <semaphore.h>
//引用了14章介绍的线程同步机制的包装类
//#inlcude "locker.h"

//一个线程同步机制的包装类
//封装信号的类

//一个线程池

template <typename T>
class threadpool
{
public:
    //thread_number是线程池中线池的数量，max_requests是请求队列中最多允许等待的、请求
    //处理的数量
    threadpool(int thread_number = 8, int max_requests = 10000);
    ~threadpool();
    //往请求队列中添加任务
    bool append(T *request);

private:
    //工作线池允许的函数它不断从工作队列中取出任务并且执行
    static void *worker(void *arg);
    void run();

private:
    int m_thread_number;        //线程池中的线池数
    int m_max_requests;         //请求队列中允许的最大请求数
    pthread_t *m_threads;       //描述线池池的数组
    std::list<T *> m_workqueue; //请求队列
    locker m_queuelocker;       //保护请求队列的互斥锁
    sem m_queuestat;            //是否有任务要处理
    bool m_stop;                //是否结束线程
};

template <typename T>
threadpool<T>::threadpool(int thread_number, int max_requests) : m_thread_number(thread_number), m_max_requests(max_requests),
                                                                 m_stop(false), m_threads(nullptr)
{
    if ((thread_number <= 0) || (max_requests <= 0))
    {
        throw std::exception();
    }
    m_threads = new pthread_t[m_thread_number];
    if (!m_threads)
    {
        throw std::exception();
    }
    //创建thread_number个线程并将他们都设置为脱离线程
    for (int i = 0; i < thread_number; ++i)
    {
            //每一个线程运行的函数都是worker()
        if (pthread_create(m_threads + i, NULL, worker, this) != 0)
        {
            delete[] m_threads;
            throw std::exception();
        }
        if (pthread_detach(m_threads[i]))//分离
        {
            delete[] m_threads;
            throw std::exception();
        }
    }
}

template <typename T>
threadpool<T>::~threadpool()
{
    delete[] m_threads;
    m_stop = true;
}

template <typename T>
bool threadpool<T>::append(T *request)
{
    //操作工作队列时要加锁 因为它被所有的线程共享
    m_queuelocker.lock();
    if (m_workqueue.size() > m_max_requests)
    {
        m_queuelocker.unlock();
        return false;
    }
    m_workqueue.push_back(request);
    m_queuelocker.unlock();
    m_queuestat.post();//pv操作
    return true;
}

template <typename T>
void *threadpool<T>::worker(void *arg)
{
    threadpool *pool = (threadpool *)arg;
    pool->run();
    return pool;
}

template <typename T>
void threadpool<T>::run()
{
    while (!m_stop)
    {
        m_queuestat.wait();
        m_queuelocker.lock();
        if (m_workqueue.empty())
        {
            m_queuelocker.unlock();
            continue;
        }
        T *request = m_workqueue.font();
        m_workqueue.pop_front();
        m_queuelocker.unlock();
        if (!request)
        {
            continue;
        }
        request->process();
    }
}

int main()
{
    return 0;
}
#endif

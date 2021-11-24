//封装一个简单的锁
class sem
{
public:
    sem()
    {
        if (sem_init(&m_sem, 0, 0) != 0)
        {
            //构造函数没有返回值 可以通过抛出异常来报告错误
            throw std::exception();
        }
    }
    //销毁信号
    ~sem()
    {
        sem_destroy(&m_sem);
    }
    //pv操作
    bool wait()
    {
        return sem_wait(&m_sem) == 0;
    }
    bool post()
    {
        return sem_post(&m_sem) == 0;
    }

private:
    sem_t m_sem;
};

//封装互斥锁的类
class locker
{
public:
    locker()
    {
        if (pthread_mutex_init(&m_mutex, NULL) != 0)
        {
            throw std::exception();
        }
    }
    ~locker()
    {
        pthread_mutex_destroy(&m_mutex);
    }
    bool lock()
    {
        return pthread_mutex_lock(&m_mutex) == 0;
    }
    bool unlock()
    {
        return pthread_mutex_unlock(&m_mutex) == 0;
    }

private:
    pthread_mutex_t m_mutex;
};
//封装条件变量的类
class cond
{
public:
    cond()
    {
        if (pthread_mutex_init(&m_mutex, nullptr) != 0)
        {
            throw std::exception();
        }
        if (pthread_cond_init(&m_cond, nullptr) != 0)
        {
            //构造函数除了问题 要把以及分配的资源释放掉
            pthread_mutex_destroy(&m_mutex);
            throw std::exception();
        }
    }
    ~cond()
    {
        pthread_mutex_destroy(&m_mutex);
        pthread_cond_destroy(&m_cond);
    }
    bool wait()
    {
        int ret = 0;
        pthread_mutex_lock(&m_mutex);
        ret = pthread_cond_wait(&m_cond, &m_mutex);
        pthread_mutex_unlock(&m_mutex);
        return ret == 0;
    }
    //唤醒等待条件变量的线程
    bool signal()
    {
        return pthread_cond_signal(&m_cond) == 0;
    }

private:
    pthread_mutex_t m_mutex;
    pthread_cond_t m_cond;
};

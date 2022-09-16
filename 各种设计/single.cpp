#include <iostream>
#include <memory>
#include <mutex>

//****************Singleton Pattern****************
class Singleton
{
private:
    static Singleton *ptrInstance;
    static std::mutex m_mutex;

    Singleton() {}

public:
    static Singleton *GetInstance()
    {
        if (ptrInstance == NULL)
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            if (ptrInstance == NULL)
            {
                ptrInstance = new Singleton();
            }
        }

        return ptrInstance;
    }

    ~Singleton()
    {
        if (ptrInstance != NULL)
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            if (ptrInstance != NULL)
            {
                delete ptrInstance;
            }
        }
    }
};
//类外赋值
std::mutex Singleton::m_mutex;
Singleton *Singleton::ptrInstance = NULL;

//单线程安全懒汉式 首次调用时才会构造对象
//实现了上述代码，发现很罗嗦，在单例类中声明该单例类的静态对象属性，要在类外定义，
//还要使用std::mutex和std::lock_guard类实现线程安全，突然想到，
//如果用下面代码实现线程安全的单例类，不是很简单嘛！
//线程安全懒汉式
//这个精简版之所以也是线程安全的，是因为，在底层对于static静态局部变量的初始化，编译器会自动加锁和解锁,卧槽 这个我不知道啊。
class Singleton2
{
private:
    Singleton2() {}

public:
    static Singleton2 *GetInstance()
    {
        static Singleton2 instance;
        return &instance;
    }
};
template <typename T>
class SingleTon
{
private:
    SingleTon() {}//私有的构造函数

public:
    static T *Instance()
    {
        static T instance;
        return &instance;
    }
}
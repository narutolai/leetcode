
#ifndef __STL_ALLOC_H
#define __STL_ALLOC_H

#include "stl_iter.h"
#include "__type_traits.h"
#if 0

#include <new>
#define __THROW_BAD_ALLOC throw bad_alloc
#elif !defined(__THROW_BAD_ALLOC)
#include <iostream>
using namespace std;
#define __THROW_BAD_ALLOC            \
    cerr << "out of memory" << endl; \
    exit(1)
#endif

//这里定义了第一级和第二级配置器
//以下是第一级配置器。
//注意，无「template 型别参数」。至于「非型别参数」inst，完全没派上用场。
template <int inst>
class __malloc_alloc_template
{
    //以下都是函式指标，所代表的函式将用来处理内存不足的情况。
private:
    static void *oom_malloc(size_t);
    static void *oom_realloc(void *, size_t);
    //函数指针
    //void (*funP)(int);   //声明也可写成void(*funP)(int x)，但习惯上一般不这样。
    //一个函数指针的设定是这样
    static void (*__malloc_alloc_oom_handler)();

public:
    static void *allocate(size_t n)
    {
        void *result = malloc(n); //第一级配置器直接使用malloc()
        // 以下，无法满足需求时，改用 oom_malloc()
        if (0 == result)
            result = oom_malloc(n);
        return result;
    }

    static void *reallocate(void *p, size_t /* old_sz */, size_t new_sz)
    {
        void *result = realloc(p, new_sz); //第一级配置器直接使用 rea
        // 以下，无法满足需求时，改用 oom_realloc()
        if (0 == result)
            result = oom_realloc(p, new_sz);
        return result;
    }

    //以下模拟 C++的 set_new_handler(). 换句话说，你可以透过它，
    // void (*f)()是一个
    static void (*set_malloc_handler(void (*f)()))()
    {
        void (*old)() = __malloc_alloc_oom_handler;
        __malloc_alloc_oom_handler = f;
        return (old);
    }
    static void deallocate(void *p, size_t)
    {
        free(p);
    }
};
//内存处理分配失败的函数指针的设定
// malloc_alloc out-of-memory handling
//初值为 0。有待客端设定。函数指针是这么写的啊卧槽
template <int inst>
void (*__malloc_alloc_template<inst>::__malloc_alloc_oom_handler)() = 0;

template <int inst>
void *__malloc_alloc_template<inst>::oom_malloc(size_t n)
{
    //函数指针的声明
    void (*my_malloc_handler)();
    void *result;
    for (;;)
    {
        //不断的释放、配置、再释放、再配置...
        my_malloc_handler = __malloc_alloc_oom_handler;
        if (0 == my_malloc_handler)
        {
            __THROW_BAD_ALLOC;
        }
        (*my_malloc_handler)(); //呼叫处理例程
        result = malloc(n);     //再次尝试配置内存
        if (result)
            return result;
    }
}

template <int inst>
void *__malloc_alloc_template<inst>::oom_realloc(void *p, size_t n)
{
    void (*my_malloc_handler)();
    void *result;
    for (;;)
    { //不断尝试释放、配置、再释放、再配置…
        my_malloc_handler = __malloc_alloc_oom_handler;
        if (0 == my_malloc_handler)
        {
            __THROW_BAD_ALLOC;
        }
        (*my_malloc_handler)(); //呼叫处理例程，企图释放内存。
        result = realloc(p, n); //再次尝试配置内存。
        if (result)
            return (result);
    }
}

//注意，以下直接将参数 inst指定为 0。
typedef __malloc_alloc_template<0> malloc_alloc;
typedef malloc_alloc alloc;





//为其包装一个接口 使得其符合STL规范
template <class T, class Alloc>
class simple_alloc
{
public:
    static T *allocate(size_t n)
    {
        return 0 == n ? 0 : (T *)Alloc::allocate(n * sizeof(T));
    }
    static T *allocate(void)
    {
        return (T *)Alloc::allocate(sizeof(T));
    }
    static void deallocate(T *p, size_t n)
    {
        if (0 != n)
            Alloc::deallocate(p, n * sizeof(T));
    }
    static void deallocate(T *p)
    {
        Alloc::deallocate(p, sizeof(T));
    }
};

#endif
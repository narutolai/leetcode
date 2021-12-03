#ifndef __STL_CONSTRUCT_H
#define __STL_CONSTRUCT_H

#include <new>
#include "__type_traits.h"
/*
依据SGI stl的标准写法 空间初始化部分，
*/
template <class T1, class T2>
inline void construct(T1 *p, const T2 &value)
{
    new (p) T1(value);
}
/*
uninitialized_copy()
first: 输入端的起始位置
last: 输出端的起始位置
result:欲初始化空间的起始处
*/

template <class InputIterator, class ForwardIterator>
inline ForwardIterator
uninitialized_copy(InputIterator first, ForwardIterator last, ForwardIterator result)
{ //依旧是利用value_type取出不first的value_type
    return __uninitialized_copy(first, last, result, value_type(result));
};
template <class InputIterator, class ForwardIterator, class T>
inline ForwardIterator
__uninitialized_copy(InputIterator first, ForwardIterator last, ForwardIterator result, T *)
{
    typedef typename __type_traits<T>::is_POD_type is_POD;
    return __uninitialized_copy_aux(first, last, result, is_POD());
    //企图利用is_POD()所获得的结果让编译器做参数推导
};

template <class InputIterator, class ForwardIterator>
inline ForwardIterator
__uninitialized_copy_aux(InputIterator first, ForwardIterator last, ForwardIterator result, _true_type)
{
    return copy(first, last, result);
    //如果是pod
};

template <class InputIterator, class ForwardIterator>
inline ForwardIterator
__uninitialized_copy_aux(InputIterator first, ForwardIterator last, ForwardIterator result, _false_type)
{
    ForwardIterator cur = result;
    for (; first != last; ++first, ++cur)
        construct(&*cur, *first);
    return cur;
    //如果不是pod类型
};
//针对char* 和 wchar_t*两种型别可以采取memove来执行复制行为。SGI设计了偏特化版本
inline char *uninitialized_copy(const char *first, const char *last, char *result)
{
    memmove(result, first, last - first);
    return result + (last - first);
};
inline wchar_t *uninitialized_copy(const wchar_t *first, const wchar_t *last, wchar_t *result)
{
    memmove(result, first, sizeof(wchar_t) * (last - first));
    return result + (last - first);
};




/*
uninitialized_fill_n
 first 指向欲初始化空间的起始处
 n表示初始化空间的大小
 x表示初值
*/

template <class ForwardIterator, class Size, class T>
inline ForwardIterator
uninitialized_fill_n(ForwardIterator first, Size n, const T &x)
{
    //利用value_type()取出 first的value_type
    return __uninitialized_fill_n(first, n, x, value_type(first));
};
//然后判断是否是POD类型
//POD是标量型别和传统的C struct型别
template <class ForwardIterator, class Size, class T, class T1>
inline ForwardIterator
__uninitialized_fill_n(ForwardIterator first, Size n, const T &x, T1 *)
{   
    //类型榨取
    typedef typename __type_traits<T1>::is_POD_type is_POD;
    return __uninitialized_fill_n_aux(first, n, x, is_POD());
};
template <class ForwardIterator, class Size, class T>
inline ForwardIterator
__uninitialized_fill_n_aux(ForwardIterator first, Size n, const T &x, _true_type)//如果是原生类型调用这个
{ 
    //高阶函数
    return fill_n(first, n, x);
};

//如果不是pod 型别
template <class ForwardIterator, class Size, class T>
inline ForwardIterator
__uninitialized_fill_n_aux(ForwardIterator first, Size n, const T &x, _false_type)//非原生类型调用这个
{ //高阶函数
    ForwardIterator cur = first;
    for (; n > 0; --n, ++cur)
        construct(&*cur, x); //stl_construct中的函数
    return cur;
};

/*
first 欲初始化空间起始处
last 指向结束处
x 表示初值
*/
template <class ForwardIterator, class T>
inline void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T &x)
{
    __uninitialized_fill(first, last, x, value_type(first));
}

template <class ForwardIterator, class T, class T1>
inline void __uninitialized_fill(ForwardIterator first, ForwardIterator last, const T &x, T1 *)
{
    typedef typename __type_traits<T1>::is_POD_type is_POD;
    __uninitialized_fill_aux(first, last, x, is_POD());
}

template <class ForwardIterator, class T>
inline void __uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T &x, _true_type)
{
    fill(first, last, x); //调用stl算法 fill()
}

template <class ForwardIterator, class T>
inline void __uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T &x, _false_type)
{
    ForwardIterator cur = first;
    for (; cur != last; ++cur)
        construct(&*cur, x); //调用stl算法 fill()
}










template <class T>
inline void destroy(T *pointer)
{
    pointer->~T(); // 调用析构函数
}

// 以下是 destroy() 第二版本，接受两个迭代器。它会设法找出元素的数值型別，
// 进而利用 __type_traits<> 求取最适当措施。
template <class ForwardIterator>
inline void destroy(ForwardIterator first, ForwardIterator last)
{
    __destroy(first, last, value_type(first));
}

// 判断元素的数值型別（value type）是否有 trivial destructor，分别调用上面的函数进行不同的处理
template <class ForwardIterator, class T>
inline void __destroy(ForwardIterator first, ForwardIterator last, T *)
{
    typedef typename __type_traits<T>::has_trivial_destructor trivial_destructor;
    __destroy_aux(first, last, trivial_destructor());
}

// 如果元素的数值型別（value type）有 trivial destructor…
template <class ForwardIterator>
inline void __destroy_aux(ForwardIterator, ForwardIterator, _true_type) {} //标量类型不需要调用析构函数

// 如果元素的数值型別（value type）有 non-trivial destructor…
template <class ForwardIterator>
inline void
__destroy_aux(ForwardIterator first, ForwardIterator last, _false_type)
{
    for (; first < last; ++first)
        destroy(&*first); //调用析构函数
}
#endif

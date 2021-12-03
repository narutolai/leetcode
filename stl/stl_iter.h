#ifndef __STL_ITER_H
#define __STL_ITER_H
/*
迭代器部分
============================================================================
*/
//5种迭代器类型
#include <cstddef>
struct input_iterator_tag
{
};
struct output_iterator_tag
{
};
struct forward_iterator_tag : public input_iterator_tag
{
};
struct bidirectional_iterator_tag : public forward_iterator_tag
{
};
struct random_access_iterator_tag : public bidirectional_iterator_tag
{
};

//根据stl规范任何一一个迭代器都要拥有5个型别定义，干脆写成一个类用来被继承
//这个类没有任何成员 只有类型定义 后面三个有默认值
//Category源自上面的5个struct
template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T *, class Reference = T &>
struct iterator
{ //这个是迭代器种类，我们知道一共有5种类型的迭代器
    typedef Category iterator_category;
    typedef T value_type;
    typedef Distance difference_type;
    typedef Pointer pointer;
    typedef Reference reference;
};

//萃取机制
template <class Iterator>
struct iterator_traits
{
    typedef typename Iterator::iterator_category iterator_category;
    typedef typename Iterator::value_type value_type;
    typedef typename Iterator::difference_type difference_type;
    typedef typename Iterator::pointer pointer;
    typedef typename Iterator::reference reference;
};
//针对原生指针而设计的traits偏特化
template <class T>
struct iterator_traits<T *>
{
    //这5种型别都要重新修改
    typedef random_access_iterator_tag iterator_category;
    typedef T value_type;
    //ptrdiff_t 为在cstddef头文件中定义
    typedef ptrdiff_t difference_type;
    typedef T *pointer;
    typedef T &reference;
};
//针对pointer-to-const而设计的traits偏特化版
template <class T>
struct iterator_traits<const T *>
{
    //这5种型别都要重新修改
    typedef random_access_iterator_tag iterator_category;
    typedef T value_type;
    //ptrdiff_t 为在cstddef头文件种定义
    typedef ptrdiff_t difference_type;
    typedef const T *pointer;
    typedef const T &reference;
};
//这个函数可以很方便的决定某个迭代器的category
template <class Iterator>
inline typename iterator_traits<Iterator>::iterator_category
iterator_category(const Iterator &)
{
    typedef typename iterator_traits<Iterator>::iterator_category category;
    return category();
}
//这个函数可以很方便决定迭代器的value_type
template <class Iterator>
inline typename iterator_traits<Iterator>::value_type *
value_type(const Iterator &)
{
    return static_cast<typename iterator_traits<Iterator>::value_type *>(0);
}

//这个函数可以很方便地决定某个迭代器的distance_type
template <class Iterator>
inline typename iterator_traits<Iterator>::difference_type *
distance_type(const Iterator &)
{
    return static_cast<typename iterator_traits<Iterator>::difference_type *>(0);
}
//以下是整组distance函数
template<class InputIterator>
inline iterator_traits<InputIterator>::difference_type
__distance(InputIterator first,InputIterator last,input_iterator_tag)
{
    iterator_traits<InputIterator>::difference_type n = 0;
    while(first!=last)
    {
        ++first;++n;
    }
    return n;
}

template<class RandomAccessIterator>
inline iterator_traits<RandomAccessIterator>::difference_type
__distance(RandomAccessIterator first,RandomAccessIterator last,random_access_iterator_tag)
{
   return last-first;
}

template<class InputIterator>
inline iterator_traits<InputIterator>::difference_type
distance(InputIterator first,InputIterator last)
{
    typedef typename iterator_traits<InputIterator>::iterator_category category;
    return __distance(first,last,category());
}



//以下是整组advance函数
template <class InputIterator, class Distance>
inline void __advance(InputIterator &i, Distance n, input_iterator_tag)
{
    while (n--)
        ++i;
}
template <class BidirectionalIterator, class Distance>
inline void __advance(BidirectionalIterator &i, Distance n, bidirectional_iterator_tag)
{
    if (n >= 0)
        while (n--)
            ++i;
    else
        while (n++)
            --i;
}
template <class RandomAccessIterator, class Distance>
inline void __advance(RandomAccessIterator &i, Distance n, random_access_iterator_tag)
{
    i += n;
}
template <class InputIterator, class Distance>
inline void advance(InputIterator &i, Distance n)
{
    __advance(i, n, iterator_category(i));
}
#endif

//SGI的 __type_traits 负责萃取型别的特性，这个东西其实是用来判断某种型别是否有non-trival的ctor
//之所以把所有的内嵌型别都定义为__false_type，是定义出了最保守的值，然后再针对每一个标量型别scalar type的设计适当的
// __type_traits 特化版本 这样就解决了问题
#ifndef __TYPE_TRAITS_H
#define __TYPE_TRAITS_H

struct _true_type
{
    /* data */
};

struct _false_type
{
    /* data */
};
//对象类型traits 看看对象是否有无关痛痒的构造函数。
//trival 就是没有意义的
//non-trival 就是有意义的
template <class type>
struct __type_traits
{
    typedef _true_type this_dummy_member_must_be_first;
    typedef _false_type has_trival_default_constructor;
    typedef _false_type has_trival_copy_constructor;
    typedef _false_type has_trival_assignment_operator;
    typedef _false_type has_trival_destructor;
    typedef _false_type is_POD_type;
};
//针对所有内置类型的特化版本
template <>
struct __type_traits<char>
{
    typedef _true_type has_trival_default_constructor;
    typedef _true_type has_trival_copy_constructor;
    typedef _true_type has_trival_assignment_operator;
    typedef _true_type has_trival_destructor;
    typedef _true_type is_POD_type;
};

template <>
struct __type_traits<signed char>
{
    typedef _true_type has_trival_default_constructor;
    typedef _true_type has_trival_copy_constructor;
    typedef _true_type has_trival_assignment_operator;
    typedef _true_type has_trival_destructor;
    typedef _true_type is_POD_type;
};

template <>
struct __type_traits<short>
{
    typedef _true_type has_trival_default_constructor;
    typedef _true_type has_trival_copy_constructor;
    typedef _true_type has_trival_assignment_operator;
    typedef _true_type has_trival_destructor;
    typedef _true_type is_POD_type;
};

template <>
struct __type_traits<long double>
{
    typedef _true_type has_trival_default_constructor; //是否有无意义的默认构造函数
    typedef _true_type has_trival_copy_constructor;    //拷贝构造函数
    typedef _true_type has_trival_assignment_operator; //拷贝赋值函数
    typedef _true_type has_trival_destructor;          //析构 函数
    typedef _true_type is_POD_type;                    //是否原生类型
};
//原生指针 也是一种标量型别
template <class T>
struct __type_traits<T *>
{
    typedef _true_type has_trival_default_constructor;
    typedef _true_type has_trival_copy_constructor;
    typedef _true_type has_trival_assignment_operator;
    typedef _true_type has_trival_destructor;
    typedef _true_type is_POD_type;
};

#endif
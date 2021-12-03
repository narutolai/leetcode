#ifndef __STL_LIST_H
#define __STL_LIST_H
#include <list>
#include "stl_alloc.h"
#include "stl_construct.h"
/*
list 节点 实际上是一个双向链表 节点里存着真正的数据
*/
template <class T>
struct __list_node
{
    typedef void *void_pointer;
    void_pointer prev;
    void_pointer next;
    T data;
};

/*
list 的迭代器 insert和splice操作是不会使得原有的list迭代器失效的，
*/
template <class T, class Ref, class Ptr>
struct __list_iterator
{
    //这个self 型别是什么啊 指向自己的吗
    typedef __list_iterator<T, T &, T *> iterator;
    typedef __list_iterator<T, Ref, Ptr> self;

    //既然是双向链表 自然也是双向迭代器 
    typedef bidirectional_iterator_tag iterator_category;
    typedef T value_type;
    typedef Ptr pointer;
    typedef Ref reference;
    typedef __list_node<T> *link_type;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

    link_type node; //指向节点的指针
    //constructor
    //使用node初始化
    __list_iterator(link_type x) : node(x) {}
    __list_iterator() {}
    //使用另一个迭代器初始化
    __list_iterator(const iterator &x) : node(x.node) {}

    bool operator==(const self &x) const { return node == x.node; }
    bool operator!=(const self &x) const { return node != x.node; }
    //对迭代器取值 取的就是节点的数据
    reference operator*() const { return (*node).data; }
    pointer operator->() const { return &(operator*()); }
    //对迭代器累加1  迭代器还是迭代器本身，但是其所指向的node 却是下一个node
    //返回值是其自身的引用
    self &operator++() //++i
    {
        node = (link_type)((*node).next);
        return *this;
    }
    self operator++(int) //i++
    {
        self tmp = *this;
        ++*this;
        return tmp;
    }
    //对迭代器缉减少1就是前一个节点
    self &operator--()
    {
        node = (link_type)((*node).prev);
        return *this;
    }
    self operator--(int)
    {
        self tmp = *this;
        --*this;
        return tmp;
    }
};

/*
lIst  数据结构
*/
template <class T, class Alloc = alloc>
class list
{
protected:
    typedef T value_type;

    typedef __list_node<T> list_node;
    typedef simple_alloc<list_node, Alloc> list_node_allocator;
    //迭代器为什么不是这样呢？？
    typedef __list_iterator<T,T,T> iterator;
public:
    typedef list_node *link_type;
    //迭代器
    typedef list_node *iterator;

public:
    iterator begin() { return (link_type)((*node).next); }
    iterator end() { return node; }
    bool empty() const { return node->next == node; }
    size_type size() const
    {
        size_type result = 0;
        distance(begin(), end(), result);
        return result;
    }

    //这个引用是从哪里来的
    reference front() { return *begin(); }
    reference back() { return *(--end()); }

    //只要一个指针，便可以表示整个环状双向链表
    //配置与释放一个节点
    link_type
    get_node()
    {
        return list_node_allocator::allocate();
    }
    void put_node(link_type p) { list_node_allocator::deallocate(p); }
    //构造一个节点
    link_type create_node(const T &x)
    {
        link_type p = get_node();
        construct(&p->data, x);
        return p;
    }
    //销毁一个节点
    void destroy_node(link_type p)
    {
        destroy(&p->data);
        put_node(p);
    }

    list() { empty_initialize(); } //产生一个空链表

    void push_back(const T &x) { insert(end(), x); }
    void push_front(const T &x) { insert(begin(), x); }
    void pop_front() { erase(begin()); }
    void pop_back()
    {
        iterator tmp = end();
        erase(--tmp);
    }
    //清除所有节点
    void clear()
    {
        link_type cur = (link_type)node->next;
        while (cur != node)
        {
            link_type tmp = cur;
            cur = (link_type)cur->next;
            destroy_node(tmp);
        }
        node->next = node;
        node->prev = node;
    }
    //将数值为value
protected:
    link_type node;
    //移除position处所指的节点
    iterator erase(iterator position)
    {
        link_type next_node = link_type(position.node->next);
        link_type prev_node = link_type(position.node->prev);
        prev_node->next = next_node;
        next_node->prev = prev_node;
        destroy_node(position.node);
        return iterator(next_node);
    }
    //在迭代器所指的位置插入一个节点
    iterator insert(iterator position, const T &x)
    { //先构造一个节点
        link_type tmp = create_node(x);
        tmp->next = position.node;
        tmp->prev = position.node->prev;
        (link_type(position.node->prev))->next = tmp;
        position.node->prev = tmp;
        return tmp;
    }
    void empty_initialize()
    {
        node = get_node(); //配置一个空节点 令node指向它
        node->next = node;
        node->prev = node;
    }
}

#endif
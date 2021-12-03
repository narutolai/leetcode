#ifndef __STL_DEQUE_H
#define __STL_DEQUE_H
#include "stl_alloc.h"
#include "stl_construct.h"
//一个全局函数
inline size_t __deque_buf_size(size_t n, size_t sz)
{
    return n != 0 ? n : (sz < 512 ? size_t(512 / sz) : size_t(1));
}

/*
deque的迭代器
*/
template <class T, class Ref, class Ptr, size_t BufSiz>
struct __deque_iterator //未继承std::iterator
{
    //这个self 型别是什么啊 指向自己的吗
    typedef __deque_iterator<T, T &, T *, BufSiz> iterator;
    typedef __deque_iterator<T, const T &, const T *, BufSiz> cosnt_iterator;
    static size_t buffer_size() { return __deque_buf_size(BufSiz, sizeof(T)); }
    typedef __deque_iterator<T, Ref, Ptr, BufSiz> self;

    //未继承st::iterator 必须亲自写5个型别
    typedef random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef Ptr pointer;
    typedef Ref reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef T **map_pointer; 

    typedef __deque_iterator self;
    //保持与容器的联系
    T *cur;
    T *first; //注意first指向第一个，但是last是指向最后一个的下一个
    T *last;
    map_pointer node; //指向一个map node
    void set_node(map_pointer new_node)
    {
        node = new_node;
        first = *new_node;
        last = first + difference_type(buffer_size());
    }
    //返回
    reference operator*() const { return *cur; }
    pointer operator->() const { return &(operator*()); }

    //两个迭代器之间的距离，其实就是所有的元素个数
    difference_type operator-(const self &x) const
    {
        return difference_type(buffer_size()) * (node - x.node - 1) + (cur - first) + (x.last - x.cur);
    }
    self &operator++()
    {
        ++cur;
        if (cur == last)
        {
            set_node(node + 1);
            cur = first;
        }
        return *this;
    }
    self operator++(int)
    {
        self tmp = *this;
        ++*this;
        return tmp;
    }
    self &operator--()
    {
        if (cur == first)
        {
            set_node(node - 1);
            cur = last;
        }
        --cur;
        return *this;
    }
    self operator--(int)
    {
        self tmp = *this;
        --*this;
        return tmp;
    }
    //以下实现随机存取 迭代器可以直接跳跃n个距离
    //其实就是要切换当前迭代器的4个成员
    self &operator+=(difference_type n)
    {
        difference_type offset = n + (cur - frist);

        //目标位置在同一个缓冲区
        if (offset >= 0 && offset < difference_type(buffer_size()))
        {
            cur += n;
        }
        else
        { //可能是加也可能是减
            difference_type node_offset =
                offset > 0 ? offset / difference_type(buffer_size()) : -difference_type((-offset - 1) / buffer_size()) - 1;
            set_node(node + node_offset);
            cur = first + (offset - node_offset * difference_type(buffer_size()));
        }
        return *this;
    }
    //返回的应该是个拷贝
    self operator+(difference_type n) const
    {
        self tmp = *this;
        return tmp += n;
    }
    self operator-=(difference_type n) { return *this += -n; }
    self operator-(difference_type n) const
    {
        self tmp = *this;
        return tmp -= n;
    }
    //实现随机存取，迭代器跳跃n个距离
    reference operator[](difference_type n) const { return *(*this + n); }
    bool operator==(const self &x) const { return cur == x.cur; }
    bool operator!=(const self &x) const { return !(*this == x); }
    bool operator<(const self &x) const
    {
        return (node == x.node) ? (cur < x.cur) : (node < x.node);
    }
};

/*
deque 数据结构
*/

template <class T, class Alloc = alloc, size_t BufSiz = 0>
class deque
{

public:
    typedef T value_type;
    typedef T *pointer;
    typedef T &reference;
    typedef size_t size_type;
    typedef __deque_iterator<T, T &, T *, BufSiz> iterator;

protected:
    typedef T **map_pointer;
    //每次配置一个元素大小
    typedef simple_alloc<value_type, Alloc> data_allocator;
    //每次配置一个指针大小
    typedef simple_alloc<pointer, Alloc> map_allocator;
    //两个迭代器
    iterator start;  //表现第一个节点
    iterator finish; //表现最后一个节点

    map_pointer map; //指向map

    size_type map_size; //map内的指针

    //有了上述结构，以下数个机能便可以轻易完成
public:
    deque(int n, const value_type &value) : start(), finish(), map(0), map_size(0)
    {
        fill_initialize(n, value);
    }
    void fill_initialize(size_t n, const value_type &value)
    {
        create_map_and_nodes(n); //把deque的结构都产生并安排好
        map_pointer cur;
        try
        {
            for (cur = start.node; cur < finish.node; ++cur)
            {
                uninitialized_fill(*cur, *cur + buffer_size(), value);
            }
            uninitialized_fill(finish.first, finish.cur, value);
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    void create_map_and_nodes(size_type num_elements)
    {
        //如果刚好整除 也会多配一个节点
        size_type num_nodes = num_elements / buffer_size() + 1;
        //一个map要管理 最少8个节点 最多是所需节点数+2
        map_size = max(initial_map_size(), num_nodes + 2);
        map = map_allocator::allocate(map_size);

        //让nstart nfinish 指向map 所拥有之全部节点的最中央区段
        //保持在最中央 可使得头尾两端的扩充能量一样大，每一个系欸按可以对应一个缓冲区
        map_pointer nstart = map + (map_size - num_nodes) / 2;
        map_pointer nfinish = nstart + num_nodes - 1;

        map_pointer cur;
        try
        {
            for (cur = nstart; cur <= nfinish; ++cur)
            {
                *cur = allocate_node();
            }
        }
        catch (const std::exception &e)
        { //commit or rollback若非全部成功，则一个不留
            std::cerr << e.what() << '\n';
        }
        //为deque的两个迭代器设置正确的内容
        start.set_node(nstart);
        finish.set_node(nfinish);
        start.cur = start.first;
        finish.cur = finish.first + num_elements % buffer_size();
    }
    iterator begin() { return start; }
    iterator end() { return finish; }
    //调用迭代器的方法
    reference operator[](size_type n)
    {
        return start[difference_type(n)];
    }
    reference front() { return *start; }
    reference back()
    {
        iterator tmp = finish;
        --tmp;
        return *tmp;
    }
    size_type size() const { return finish - start; }
    size_type max_size() const { return size_type(-1); }
    bool empty() const { return finish == start; }

    void push_back(const value_type &t)
    {
        //最后的缓冲区有一个以上的备用空间，注意是1个以上
        if (finish.cur != finish.last - 1)
        {
            construct(finish.cur, t);
            ++finish.cur;
        }
        else
        {
            push_back_aux(t);
        }
    }
    void push_back_aux(const value_type &t)
    {
        value_type t_copy = t;
        reserve_map_at_back();               //若符合某种条件则必须重新换一个map
        *(finish.node + 1) = allocate_node() //配置一个新节点
        try
        {
            construct(finish.cur, t_copy);
            finish.set_node(finish.node - 1);
            finish.cur = finish.first;
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    void push_front(const value_type &t)
    {
        if (start.cur != start.first)
        {
            construct(start.cur - 1, t);
            --start.cur;
        }
        else
        {
            push_front_aux(t);
        }
    }
    void push_front_aux(const value_type &t)
    {
        value_type t_copy = t;
        reserve_map_at_front();
        *(start.node - 1) = allocate_node();
        try
        {
            start.set_node(start.node - 1);
            start.cur = start.last - 1;
            construct(start.cur, t_copy);
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            start.set_node(start.node + 1);
            start.cur = start.first;
            deallocate_node(*(start.node - 1));
            throw;
        }
    }
    void reserve_map_at_front(size_type nodes_to _add = 1)
    {
        if (nodes_to_add + 1 > map_size - (finish.node - map))
        {
            reallocate_map(nodes_to_add, false);
        }
    }
    void reserve_map_at_back(size_type nodes_to_add = 1)
    {
        if (nodes_to_add > start.node - map)
        {
            reallocate_map(nodes_to_add, true);
        }
    }
    void reallocate_map(size_type nodes_to_add, bool add_at_front)
    {
        size_type old_num_nodes = finish.node - start.node + 1;
        size_type new_num_nodes = old_num_nodes + nodes_to_add;

        map_pointer new_nstart;
        if (map_size > 2 * new_num_nodes)
        {
            new_num_nodes = map + (map_size - new_num_nodes)/2+(add_at_front?nodes_to_add:0);
            if(new_nstart<start.node)
            {
                copy(start.node,finish.node+1,new_nstart+old_num_nodes);
            }
            else
            {
                size_type new_map_size=map_size +max(map_size,nodes_to_add)+2;
                //配置一块新空间给map使用
                map_pointer new_map =map_allocator::allocate(new_map_size);
                new_nstart =new_map +(new_map_size-new_num_nodes)/2+(add_at_front?nodes_to_add:0);
                //把原map内容拷贝过来
                copy(start.node,finish.node+1,new_nstart);
                //释放原map
                map_allocator::deallocate(map,map_size);
                map = new_map;
                map_size =new_map_size;
            }
            //重新设定迭代器start和finish
            start.set_node(new_nstart);
            finish.set_node(new_nstart+old_num_nodes-1);
        }
    }
    void pop_back()
    {
        //如果最后一个缓冲区有多个元素
        if (finish.cur != finish.first)
        {
            --finish.cur
                  destroy(finish.cur);
        }
        else
        { //如果最后指针没有任何元素，进行缓冲区的释放操作
            pop_back_aux();
        }
    }
    void pop_back_aux()
    {
        deallocate_node(finish.first);    //释放最后一个缓冲区
        finish.set_node(finish.node - 1); //调整finish的指向
        finish.cur = finish.last - 1;
        destroy(finish.cur);
    }
    void pop_front()
    {
        //start缓冲区有一个或多个元素
        if (start.cur != start.last - 1)
        {
            destroy(start.cur); //销毁第一个
            ++start.cur;        //调整该指针
        }
        else
        {
            pop_front_aux();
        }
    }
    //start.cur==start.last-1
    void pop_front_aux()
    {
        destroy(start.cur);
        deallocate_node(start.first);
        start.set_node(start.node + 1);
        start.cur = start.first;
    }

}

#endif
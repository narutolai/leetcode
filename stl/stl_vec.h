/*
根据stl规定
*/
#include "stl_alloc.h"
#include "stl_construct.h"
template <class T, class Alloc = alloc>
class vector
{
public:
    //vector的型别定义
    typedef T value_type;
    typedef value_type *pointer;
    //vector的迭代器就是普通指针
    typedef value_type *iterator;
    typedef value_type &reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

protected:
    //这个用的是stl_alloc.h中的分配器
    typedef simple_alloc<value_type, Alloc> data_allocator;
    //三个指针 足够 因为是连续空间？？
    iterator start;//表示目前使用的空间的头
    iterator finish;//表示目前使用的空间的尾
    iterator end_of_storage; //表示目前可用空间的尾
    //没有备用空间的时候调用这个函数 也就是当finish=end_of_storage的时候
    void insert_aux(iterator position, const T &x)
    {
        if (finish != end_of_storage)
        {
            construct(finish, *(finish - 1));
            ++finish;

            T x_copy = x;
            copy_backward(position, finish - 2, finish - 1);
            *position = x_copy;
        }
        else
        {
            const size_type old_size = size();
            const size_type len = old_size != 0 ? 2 * old_size : 1;
            //以上配置原则：如果原大小为0 则配置1个元素大小
            //如果原大小不为0 则配置原大小的两倍
            //前半段用来放置原数据，后半段准备用来放置新数据

            //所谓动态增加大小不是在原空间后接新的空间 因为这样无法保证原空间之后尚有可以配置的空间，而是以
            //原空间的两倍大小配置另外的一块较大的空间。
            iterator new_start = data_allocator::allocate(len);
            iterator new_finish = new_start;
            try
            {
                //将原vector的内容拷贝到新的vector
                new_finish = uninitialized_copy(start, position, new_start);
                construct(new_finish, x);
                ++new_finish;
                new_finish = uninitialized(position, finish, new_finish);
            }
            catch (const std::exception &e)
            {
                destroy(new_start, new_finish);
                data_allocator::deallocate(new_start, len);
                throw;
            }
            //析构原vector
            destroy(begin(), end());
            deallocate();
            //调整迭代器 指向新的vector
            start = new_start;
            finish = new_finish;
            end_of_storage = new_start + len;
        }
    }
    void deallocate()
    {
        if (start)
            data_allocator::deallocate(start, end_of_storage - start);
    }
    //填充并初始化
    void fill_initialize(size_type n,const T& value)
    {
        start = allocate_and_fill(n,value);
        finish =start+n;
        end_of_storage = finish;
    }

public:
//返回开始指针
    iterator begin() { return start; }
    //返回结束指针
    iterator end() { return finish; }
    //这个是不是还要重载迭代器的减法
    size_type size() const { return size_type(end() - begin()); }
    size_type capacity() const { return size_type(end_of_storage - begin()); }

    bool empty() const { return begin() == end(); }
    reference operator[](size_type n) { return *(begin() + n); }
    
    reference front() { return *begin(); }  //第一个元素
    reference back() { return *(end() - 1); } //最后一个元素

    //整个vector只有这三个指针要初始化
    vector() : start(0), finish(0), end_of_storage(0) {}
    vector(size_type n, const T &value) { fill_initialize(n, value); }
    vector(int n,const T&value) {fill_initialize(n,value);}
    vector(long n,const T&value) {fill_initialize(n,value);}
    ~vector()
    {
        //全局函数在stl_construct.h中
        destroy(start, finish);
        //vector的一个成员函数
        deallocate();
    }

    void push_back(const T &x)
    {
        if (finish != end_of_storage)  //还有备用空间
        { 
            construct(finish, x);        //全局函数    
            ++finish;                   //调整水位高度
        }
        else    
        {
            insert_aux(end(), x); //        没有备用空间
        }
    }
    void pop_back()
    {
        --finish;
        destroy(finish); //全局函数
    }

    //清除某个位置上的函数
    iterator erase(iterator positon)
    {
        if (positon + 1 != end())
            copy(positon + 1, finish, positon);
        --finish;
        destroy(finish);
        return positon;
    }
    void resize(size_type new_size, const T &x)
    {
        if (new_size < size())
            erase(begin() + new_size, end());
        else
            insert(end(), new_size - size(), x);
    }
    void resize(size_type new_size) { return resize(new_size, T()); }
    void clear() { erase(begin(), end()); }
    
protected:
    //配置空间并填满内容
    iterator allocate_and_fill(size_type n, const T &x)
    {
        iterator result = data_allocator::allocate(n);
        //全局函数
        uninitialized_fill_n(result, n, x);
        return result;
    }
};
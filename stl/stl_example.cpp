/*
根据stl的规范实现一个简单的allocator
空间配置器的简单实现
空间配置器的作用：
（1）将对象构造和内存开辟进行分离。
（2）将对象析构和内存释放进行分离。
空间配置器的主要函数：
1.allocate：  进行内存的开辟，底层调用的就是malloc。
2.deallocate：进行内存的释放，底层调用的就是free。
3.construct ：使用new来负责给容器中的对象进行构造。
4.destroy：   负责析构容器中的对象。p->~T()。
*/
template <typename T>
class allocator
{
public:
    typedef T value_type;
    typedef T *pointer;
    typedef const T *const_pointer;
    typedef T &reference;
    typedef const T &const_reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

public:
    template <class U>
    struct rebind
    {
        typedef allocator<U> other;
    };
    allocator(){};
    allocator(const allocator &) {}

    template <class U>
    allocator(const allocator<U> &) {}
    ~allocator() {}

    pointer address(reference x) const { return (pointer)&x; }
    const_pointer const_address(const_reference x) const { return (const_pointer)&x; }
    pointer allocate(size_type n, const void *= 0)
    {
        T *temp = (T *)(::operator new((size_t)(n * sizeof(T))));
        if (temp == 0)
        {
            cerr << "out of memory" << endl;
            exit(1);
        }
        return temp;
    }
    void deallocate(pointer p, size_type n)
    {
        ::operator delete(p);
    }

    size_type max_size() const { return size_type(UINT_MAX / sizeof(T)); }
    void construct(pointer p, const T &value)
    {
        new (p) T1(value);
    }
    void destroy(pointer p) { p->~T(); }
};



//针对vec的迭代器
template <typename T>
class vecierator : public iterator<>
{

};


//泛型算法 find之类的
template <class InputIterator, class Type>
InputIterator find(InputIterator first, InputIterator last, const Type &value)
{
    while (first != last && *first != value)
        ++first;
    return first;
}

//仿函数

//适配器

int main()
{

    return 0;
}
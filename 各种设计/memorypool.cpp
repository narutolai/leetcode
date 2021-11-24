#include <stdint.h>
#include <mutex>
#include <iostream>
using namespace std;

/**
 * 一个简单内存池的实现
 * C++程序默认的内存管理（new，delete，malloc，free）会频繁地在堆上分配和释放内存，导致性能的损失，产生大量的内存碎片，
 * 降低内存的利用率。默认的内存管理因为被设计的比较通用，所以在性能上并不能做到极致。
 * 因此，很多时候需要根据业务需求设计专用内存管理器，便于针对特定数据结构和使用场合的内存管理，比如：内存池。
 * https://zhuanlan.zhihu.com/p/64719710 一个经典内存池的实现
*/

//单个的大小和个数
template <size_t BlockSize, size_t BlockNum>
class MemoryPool
{
private:
    struct FreeBlock
    {
        unsigned char data[BlockSize]; //这么多个字节
        FreeBlock *next;
    };
    struct MemChunk
    {
        FreeBlock blocks[BlockNum];
        MemChunk *next;
    };
    MemChunk *mem_chunk_head;
    FreeBlock *free_block_head;
    std::mutex mtx;
    std::mutex array_mtx;

public:
    MemoryPool()
    {
        cout<<"memory pool  construct" <<endl;
        std::lock_guard<std::mutex> lk(mtx);
        free_block_head = nullptr;
        mem_chunk_head = nullptr;
    }
    ~MemoryPool()
    {
        cout<<"memory pool  deconstruct" <<endl;
        std::lock_guard<std::mutex> lk(mtx);
        MemChunk *p;
        while (mem_chunk_head)
        {
            p = mem_chunk_head->next;
            delete mem_chunk_head;
            mem_chunk_head = p;
        }
    }
    //返回
    void *allocate()
    {
        std::lock_guard<std::mutex> lk(mtx);
        //当前无trunk可用
        if (!free_block_head)
        {
            //先分配一块trunk
            MemChunk *new_chunk = new MemChunk;
            new_chunk->next = nullptr;

            //设置空闲头节点并把trunk相连接
            free_block_head = &(new_chunk->blocks[0]);
            for (int i = 1; i < BlockNum; i++)
            {
                new_chunk->blocks[i - 1].next = &(new_chunk->blocks[i]);
            }
            new_chunk->blocks[BlockNum - 1].next = nullptr;

            //首次分配
            if (!mem_chunk_head)
                mem_chunk_head = new_chunk;
            else
            { //设置mem_trunk头节点
                mem_chunk_head->next = new_chunk;
                mem_chunk_head = new_chunk;
            }
        }

        //直接取出空闲头节点
        void *object_block = free_block_head;
        //设置头节点为其下一个
        free_block_head = free_block_head->next;

        return object_block;
    }

    void *allocate(size_t size)
    {
        std::lock_guard<std::mutex> lk(array_mtx);

        int n = size / BlockSize;
        void *p = allocate();

        for (int i = 1; i < n; i++)
            allocate();
        return p;
    }

    void deallocate(void *p)
    {
        std::lock_guard<std::mutex> lk(mtx);

        FreeBlock *block = static_cast<FreeBlock *>(p);
        block->next = free_block_head;
        free_block_head = block;
    }
};

class MyObject
{
    int data;

public:
    MyObject(int x) : data(x)
    {
        cout << "construcnt" << endl;
    }
    ~MyObject()
    {
        cout << "deconstruct" << endl;
    }

    void *operator new[](size_t size);
    void operator delete[](void *p);
    void *operator new(size_t size);
    void operator delete(void *p);
};
//一块trunk  10个object。
MemoryPool<sizeof(MyObject), 10> gMemPool;
//通过重载new和delete操作符来使用
void *MyObject::operator new(size_t size)
{
    //这个重载的不需要调用构造函数吗
    cout << "pool new" << endl;
    return gMemPool.allocate();
}
void MyObject::operator delete(void *p)
{
    //这里不需要调用析构函数的吗
    cout << "pool delete" << endl;
    gMemPool.deallocate(p);
}

// class test
// {
// public:
//     void *operator new(size_t n) //new 重载操作符号规定必须参数为n 然后返回值是 void *
//     {
//         cout << "fuck you?" << endl;
//         return NULL;
//     }
// };
int main()
{
    //我都不知道怎么用，，，，，，
    // new test; //输出fuckyou

    /**用法就在于重载new 和delete ,当你使用了内存池后，
     * 对象的new 和delete不是真正的调用系统操作符new和delete
     * 而是直接从中取出节点，可以少调用几次malloc()了
    */

    //我觉得是先调用 构造函数 MyObject(1) 临时对象 new(sizeof(MyObject(1)))
    cout<<"=================="<<endl;
    
    
    /**
     * 重载了new 和delete 后，调用顺序为， 构造函数->new  析构函数->delete
     * 为什么是这样的顺序呢，因为构造函数可能要先申请别的堆区内存，所以你先申请好，
     * 析构时 则是先析构你申请的堆区内容，再调用delete 把你析构。
     * 
     * 此外我原先以为 类的构造和析构函数 是显示的在new 和operator中被调用，现在重载后看来不是
     * 这样的，可能是汇编时会自动添加吧。 
     * 
     * 不要显示调用析构函数，因为一般析构函数中会释放堆区的内存，后面如果再调用delete ,就会重复
     * 释放 就会报错的。
    */
    {
        MyObject *my = new MyObject(1);
        //my->MyObject(2); can't pass 不能显示调用构造函数
       // my->~MyObject(); pass         可以显示调用析构函数.
        delete my;
    }


    //总之  受益匪浅！！！

    cout<<"=================="<<endl;
    return 0;
}

//简单进程池

//简单线程池

//简单内存池

//并发版本！！锁的运用

//模板元编程

//负载均衡算法

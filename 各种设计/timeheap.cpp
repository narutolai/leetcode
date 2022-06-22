#ifndef MIN_HEAP
#define MIN_HEAP

#include <iostream>
#include <netinet/in.h>
#include <time.h>

using std::exception;

#define BUFFER_SIZE 64
//前向声明
class heap_timer;
struct client_data
{
	sockaddr_in address;
	int sockfd;
	char buf[BUFFER_SIZE];
	heap_timer *timer;
};

class heap_timer
{
public:
	heap_timer(int delay)
	{
		expire = time(NULL) + delay;
	}

public:
	time_t expire;
	void (*cb_func)(client_data *);
	client_data *user_data;
};
//时间堆类

class time_heap
{
	//先把构造和析构函数写完
public:
	time_heap(int cap) throw(std::exception) : capacity(cap), cur_size(0)
	{
		array = new heap_timer *[capacity];
		if (!array)
		{
			throw std::exception();
		}
		for (int i = 0; i < capacity; ++i)
		{
			array[i] = NULL;
		}
	}
	time_heap(heap_timer **init_array, int size, int capacity) throw(std::exception) : cur_size(size), capacity(capacity)
	{
		if (capacity < size)
		{
			throw std::exception();
		}
		array = new heap_timer *[capacity];
		if (!array)
		{
			throw std::exception();
		}
		for (int i = 0; i < capacity; ++i)
		{
			array[i] = NULL;
		}
		if (size != 0)
		{
			for (int i = 0; i < size; i++)
			{
				array[i] = init_array[i];
			}
			for (int i = (cur_size - 1) / 2; i >= 0; --i)
			{
				percolate_down(i);
			}
		}
	}
	~time_heap()
	{
		for (int i = 0; i < cur_size; i++)
		{
			delete array[i];
		}
		delete[] array;
	}

private:
	void add_timer(heap_timer *timer) throw(std::exception)
	{
		if (!timer)
			return;
		if (cur_size >= capacity)
		{
			resize();
		}
		//新加一个元素
		int hole = cur_size++;
		int parent = 0;
		//
		while (hole > 0)
		{
			//父节点
			parent = (hole - 1) / 2;
			if (array[parent]->expire <= timer->expire)
			{
				break;
			}
			//父节点移动
			array[hole] = array[parent];
			hole = parent;
		}
		array[hole] = timer;
	}

	void del_timer(heap_timer *timer)
	{
		if (!timer)
		{
			return;
		}
		timer->cb_func = NULL;
	}
	heap_timer *top() const
	{
		if (empty())
			return NULL;
		return array[0];
	}

	void pop_timer()
	{
		if (empty())
		{
			return;
		}
		if (array[0])
		{
			delete array[0];
			array[0] = array[--cur_size];
			percolate_down(0);
		}
	}
	void tick()
	{
		heap_timer *tmp = array[0];
		time_t cur = time(NULL);

		while (!empty())
		{
			if (!tmp)
			{
				break;
			}
			//如果堆顶元素 没有到期 则退出循环
			if (tmp->expire > cur)
			{
				break;
			}
			//否则执行 任务
			if (array[0]->cb_func)
			{
				array[0]->cb_func(array[0]->user_data);
				pop_timer();
				tmp = array[0];
			}
		}
	}
	bool empty() const { return cur_size == 0; }

private:
	void percolate_down(int hole)
	{
		heap_timer *temp = array[hole];
		for (int child = 2 * hole + 1; child <= cur_size - 1; child = 2 * child + 1)
		{
			if (child + 1 < cur_size && array[child]->expire > array[child + 1]->expire)
			{
				child++;
			}
			if (array[child]->expire < temp->expire)
			{
				array[hole] = array[child];
				hole = child;
			}
		}
		array[hole] = temp;
	}
	void resize() throw(std::exception)
	{
		heap_timer **temp = new heap_timer *[2 * capacity];
		for (int i = 0; i < 2 * capacity; ++i)
		{
			temp[i] = NULL;
		}
		if (!temp)
		{
			throw std::exception();
		}
		capacity = 2 * capacity;
		for (int i = 0; i < cur_size; ++i)
		{
			temp[i] = array[i];
		}
		delete[] array;
		array = temp;
	}

private:
	heap_timer **array;
	int capacity;
	int cur_size;
};
int main()
{
}
#endif

#include<stdio.h>
#include <time.h>
#include <netinet/in.h>



void func(void *arg)
{
    time_t time = *(time_t*)arg;
    printf("clocker.....%s",ctime(&time));
}



class heap_timer
{
    public:
        heap_timer(int delay)
        {
            expire = time(NULL) + delay;
        }
        time_t expire;
        void (*cb_func)(void*arg);
        void *arg;
};

class time_heap
{
    public:
        time_heap(int cap):m_Cap(cap),m_Size(0)
        {
            array = new heap_timer *[cap];
            for (int i = 0; i < cap; ++i)
            {
                array[i] = NULL;
            }
        }
        time_heap(heap_timer** init_array, int size, int capacity) :m_Size(size), m_Cap(capacity)
    {
        //略
        
    }
        ~time_heap()
        {
            for (int i = 0 ; i < m_Size ; ++i)
            {
                delete array[i];
            }
            delete array;
        }
    public:
        void tick()
        {
            heap_timer *timer = array[0];
            time_t cur =  time(NULL);

            while (!empty())
            {
                if(!timer)
                    break;

                if(timer->expire > cur) //堆顶定时器没有到期 则退出
                    break;
                
                if(timer->cb_func)
                {
                      timer->cb_func(timer->arg); //执行定时器
                      pop_timer();
                      timer = array[0];
                }
            }

        }
    private:
        void resize(){
            heap_timer** temp =  new heap_timer*[2 * m_Cap];
           
            m_Cap = 2* m_Cap;
            for (int i = 0; i < m_Size; ++i)
            {
                temp[i] = array[i];
            }
            delete[] array;
            array = temp;
        }
    public:

        void add_timer(heap_timer* timer) //向一个堆添加一个节点
        {
            if (!timer)return;
            if(m_Size > m_Cap)
                resize();
            
            int hole = m_Size++;  //添加的新hole
            int parent =0;
            while (hole > 0)
            {
                parent = (hole - 1) / 2;
                if(timer->expire > array[parent]->expire) //应该是金字塔形状的
                    break;
               
                array[hole] = array[parent];
                hole = parent;
            }
            array[hole] = timer;
        }
        void del_timer(heap_timer* timer)//假删除
        {
            if(!timer )
            {
                return;
            }
            timer->cb_func = NULL;
        }
        heap_timer * top()const
        {
            if(empty())
                return NULL;
            return array[0];
        }
        void pop_timer()
        {
            if(empty())
                return ;
            if(array[0])
            {
                delete array[0];
                array[0] = array[--m_Size]; //弹出第一个 把最后一个移动到首位 然后再调整堆
                adjust_down(0);
            }
        }
        void adjust_down(int hole)
        {
            heap_timer *timer = array[hole];
            for (int child = 2*hole +1 ; child < m_Size; child = 2*child + 1) //找到两个子节点中的较小值 换上去
            {
                if(array[child]->expire > array[child + 1]->expire && child +1 <m_Size)
                {
                    child++;
                }
                if(timer->expire > array[child]->expire)
                {
                    array[hole] = array[child];
                    hole = child;
                }
            }
            array[hole] = timer;
        }
        bool empty()const{return m_Size == 0;}
        
        void showtime()
        {
            for (int i = 0; i < m_Size;++i)
            {
                printf(" exist timer: %d,  %s \n",i, ctime(&array[i]->expire));
            }
        }
    private:
        
        heap_timer ** array;
        int m_Cap;
        int m_Size;
};


int main()
{
    time_t iNow = time(NULL);
    printf("now %s",ctime(&iNow));
    time_heap  tmHeap(20);

    for (int i = 0; i < 10; i++)
    {
        heap_timer *htim = new heap_timer((i + 1) * 5);
        htim->cb_func = func;
        htim->arg = (void*)&htim->expire;

        tmHeap.add_timer(htim);
    }
    tmHeap.showtime();
    while(1)
    {
        tmHeap.tick();
    }
    return 0;
}


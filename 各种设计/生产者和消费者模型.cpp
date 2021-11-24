//https://blog.csdn.net/JMW1407/article/details/108487490

#include <iostream>
using namespace std;
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <windows.h>
//生产者数量
#define PRODUCT_SIZE 20
//消费者数量
#define CUSTOMER_SIZE 1
//最大产品数量
#define MAX_SIZE 10
//互斥锁
mutex mut;
//条件变量
condition_variable con;
//队列，模拟缓冲区
queue<int> que;
void Producter()
{

    while (true)
    {
        Sleep(10);
        std::unique_lock<std::mutex> lck(mut);
        while (que.size() > MAX_SIZE)
        {
            con.wait(lck);
        }
        int data = rand();
        que.push(data);
        cout << this_thread::get_id() << "生产了产品：" << data << endl;
        con.notify_all();
    }
}
void Customer()
{
    while (true)
    {
        std::unique_lock<std::mutex> lck(mut);
        while (que.empty())
        {
            con.wait(lck);
        }
        cout << this_thread::get_id() << "消费了产品：" << que.front() << endl;
        que.pop();
        con.notify_all();
    }
}
int main()
{
    vector<thread> threadPoll;
    //创建生产者和消费者
    for (int i = 0; i < PRODUCT_SIZE; ++i)
    {
        threadPoll.push_back(thread(Producter));
    }
    for (int i = 0; i < PRODUCT_SIZE + CUSTOMER_SIZE; ++i)
    {
        threadPoll.push_back(thread(Customer));
    }

    for (int i = 0; i < PRODUCT_SIZE + CUSTOMER_SIZE; ++i)
    {
        threadPoll[i].join();
    }

    return 0;
}
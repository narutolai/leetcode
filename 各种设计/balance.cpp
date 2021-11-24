
#include <iostream>
#include <ctime>
#include <vector>
#include <numeric>
#include <mutex>
using namespace std;
//负载均衡算法的实现
class loadBalance
{

private:
    vector<int> serverAddrs; //代表服务器列表

    int index = 0;
    int size;

public:
    loadBalance() {}
    loadBalance(vector<int> &nums) : serverAddrs(nums), size(nums.size()), count(0.0)
    {
        sum = accumulate(serverAddrs.begin(), serverAddrs.end(), 0);
        usedCount.resize(nums.size());
    }
    //随机算法
    int Random()
    {
        srand((int)time(0));
        return rand() % serverAddrs.size();
    }

    //轮询算法
    int oneByOne()
    {
        std::lock_guard<std::mutex> lock(mutex);
        if (index == serverAddrs.size())
        {
            index = 0;
        }
        return serverAddrs[index++];
    }
    //轮询加权 根据每一台服务器的不同的能力 分配权重 连接数  响应速度 性能分配不同的权重。
    //用一个全局map保存一个序列中当前服务器的使用次数

    vector<int> usedCount;

    int oneByOneWithWeight()
    {
        std::lock_guard<std::mutex> lock(mutex);
        for (int i = 0; i < serverAddrs.size(); i++)
        {
            if (usedCount[i] < serverAddrs[i])
            {
                usedCount[i]++;
                return i;
            }
        }
        fill_n(usedCount.begin(), serverAddrs.size(), 0);
        usedCount[0]++;
        return 0;
    }

    //随机加权c++有随机算法 注意平方跟计算要浮点数。
    float count;
    float sum;
    //只要分母是浮点数 那么最后结果就会自动转化。
    int RandomWithWeight()
    {
        //随机
        count++;
        int ind = 0;
        float minnum = INT_MAX;
        for (int i = 0; i < size; i++)
        {
            usedCount[i]++;
            float tempsum = 0.0;
            for (int j = 0; j < size; j++)
            {
                tempsum += (usedCount[j] / count - serverAddrs[j] / sum) * (usedCount[j] / count - serverAddrs[j] / sum);
            }
            usedCount[i]--;
            if (tempsum < minnum)
            {
                minnum = tempsum;
                ind = i;
            }
        }
        usedCount[ind]++;
        return ind;
    }
    //根据用户ip 哈希访问。
    int ipHash()
    {
        // hashfunc(ip)%addr.size();
        return 0;
    }

    //ip-HASH  这个方式可以保证同一个ip落到同一个服务器上

    //总结：负载均衡要考虑多个方面 可能是服务器本身:性能 连接数 相应速度 也可能是用户方。
};
//我靠  不访问 不用初化？
//int loadBalance::index = 0;
#include <algorithm>
#include <map>
int main()
{
    vector<int> nums{1, 2, 3, 4};
    loadBalance lo(nums);

    vector<int> count(4);
    for (int i = 0; i < 10000; i++)
    {
        count[lo.RandomWithWeight()]++;
    }

    for_each(count.begin(), count.end(), [](int &num) { cout << num << endl; });
    // for (int i = 0; i < 5; i++)
    //     cout << lo.oneByOneWithWeight() << " ";
    // cout << endl;
    //  for (int i = 0; i < 15; i++)
    //     cout << lo.oneByOne() << " ";
    // cout << endl;

    return 0;
}

//  * 问：随机和轮询有什么区别吗？
//  * 答：随机是基于统计的，当实验次数足够多的时候，会体现基于权重的分布态势，
//  * 但是轮询 是一个基于权重的一个序列的序列的循环。
//  *
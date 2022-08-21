// 今天，书店老板有一家店打算试营业 customers.length 分钟。
//每分钟都有一些顾客（customers[i]）会进入书店，所有这些顾客都会在那一分钟结束后离开。

// 在某些时候，书店老板会生气。 如果书店老板在第 i 分钟生气，那么 grumpy[i] = 1，否则 grumpy[i] = 0。
//当书店老板生气时，那一分钟的顾客就会不满意，不生气则他们是满意的。
// 书店老板知道一个秘密技巧，能抑制自己的情绪，可以让自己连续 X 分钟不生气，但却只能使用一次。

// 请你返回这一天营业下来，最多有多少客户能够感到满意的数量。

// 示例：

// 输入：customers = [1,0,1,2,1,1,7,5], grumpy = [0,1,0,1,0,1,0,1], X = 3
// 输出：16
// 解释：
// 书店老板在最后 3 分钟保持冷静。
// 感到满意的最大客户数量 = 1 + 1 + 1 + 1 + 7 + 5 = 16.

class Solution
{
public:
    int maxSatisfied(vector<int> &customers, vector<int> &grumpy, int X)
    {
        if (X >= grumpy.size())
            return accumulate(customers.begin(), customers.end(), 0);
        int sum = 0;
        for (int i = 0; i < customers.size(); i++)
        {
            if (!grumpy[i])
            {
                sum += customers[i];
                //这里改进点将累加后的赋0 这样下面就只需要一个for循环就行了
                customers[i] = 0;
            }
        }

        //其实就是计算这个大小为X的滑动窗口内的最大值为多少。
        int result = 0, add = 0;
        for (int i = 0, j = 0; i < grumpy.size(); i++)
        {
            add += customers[i];
            if (i - j + 1 > X)
            { //把窗口外的值删去。同时j++
                add -= customers[j++];
            }
            result = max(result, add);
        }
        return result + sum;
    }
};
//遍历次数 2
//假设老板没有这个秘密技巧。那么我们可以算出有多少顾客满意，现在有了这个技巧后，满意的顾客数肯定是在原来的基础上累加
//所以我们可以先把不使用技巧可以满意的顾客数量累加。然后加完置0，然后遍历一个x大小的窗口，然后看窗口内的值最大可以为多少。
//注意点是 怎么滑动窗口
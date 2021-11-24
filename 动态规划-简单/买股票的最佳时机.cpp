// 给定一个数组，它的第 i 个元素是一支给定股票第 i 天的价格。

// 如果你最多只允许完成一笔交易（即买入和卖出一支股票一次），设计一个算法来计算你所能获取的最大利润。

// 注意：你不能在买入股票前卖出股票。

//给定 股票价格  还有交易次数k  还有冷冻期 ， 实际上是三维dP数组  然后去填值 填这个数组大概是这样的。
class Solution
{
public:
    int maxProfit(vector<int> &prices, int k = 1) //k=1
    {
        //状态转移方程很重要
        int dp_i_0 = 0, dp_i_1 = INT_MIN;

        for (int i = 0; i < prices.size(); i++)
        {
            //当前的dp           上一个的dp
            dp_i_0 = max(dp_i_0, dp_i_1 + prices[i]);
            dp_i_1 = max(dp_i_1, -prices[i]);
        }
        return dp_i_0;
    }
    int maxProfit(vector<int> &prices, int k = INT_MAX) //k=正无穷
    {
        //状态转移方程很重要
        int dp_i_0 = 0, dp_i_1 = INT_MIN;

        for (int i = 0; i < prices.size(); i++)
        {
            int temp = dp_i_0;                        //要把之前的dp_i_0存起来
            dp_i_0 = max(dp_i_0, dp_i_1 + prices[i]); //这个dp_i_0会被更新
            dp_i_1 = max(dp_i_1, temp - prices[i]);
        }
        return dp_i_0;
    }

    int maxProfit(vector<int> &prices, int k = INT_MAX, int cooldown = 1) //k=正无穷 还有冷却时间 就是两次操作之间有cd
    {
        //状态转移方程很重要
        int dp_i_0 = 0, dp_i_1 = INT_MIN;
        int dp_pre_0 = 0; //表示dp[i-2][0];
        for (int i = 0; i < prices.size(); i++)
        {
            int temp = dp_i_0;                        //要把之前的dp_i_0存起来
            dp_i_0 = max(dp_i_0, dp_i_1 + prices[i]); //这个dp_i_0会被更新
            dp_i_1 = max(dp_i_1, dp_pre_0 - prices[i]);
            dp_pre_0 = temp;
        }
        return dp_i_0;
    }

    int maxProfit(vector<int> &prices, int k = INT_MAX, int fee = 1) //k=正无穷 还有手续费
    {
        //状态转移方程很重要
        int dp_i_0 = 0, dp_i_1 = INT_MIN;
        for (int i = 0; i < prices.size(); i++)
        {
            int temp = dp_i_0;                            //要把之前的dp_i_0存起来
            dp_i_0 = max(dp_i_0, dp_i_1 + prices[i]);     //这个dp_i_0会被更新
            dp_i_1 = max(dp_i_1, temp - prices[i] - fee); //这里减去手续费用
        }
        return dp_i_0;
    }
    
    int maxProfit(vector<int> &prices, int k = 2) //k=2
    {
        //状态转移方程很重要
        int dp_i1_0 = 0, dp_i1_1 = INT_MIN;
        int dp_i2_0 = 0, dp_i2_1 = INT_MIN;
        for (int i = 0; i < prices.size(); i++)
        {
            dp_i2_0 = max(dp_i2_0, dp_i2_1 + prices[i]);
            dp_i2_1 = max(dp_i1_1, dp_i2_0 - prices[i]);

            dp_i1_0 = max(dp_i1_0, dp_i1_1 + prices[i]); //这个dp_i_0会被更新
            dp_i1_1 = max(dp_i1_1, -prices[i]);
        }
        return dp_i_0;
    }
};

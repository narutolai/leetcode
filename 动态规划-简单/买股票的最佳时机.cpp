// 给定一个数组，它的第 i 个元素是一支给定股票第 i 天的价格。

// 如果你最多只允许完成一笔交易（即买入和卖出一支股票一次），设计一个算法来计算你所能获取的最大利润。

// 注意：你不能在买入股票前卖出股票。

//给定 股票价格  还有交易次数k  还有冷冻期 ， 实际上是三维dP数组  然后去填值 填这个数组大概是这样的。
class Solution
{
public:
    //正常版本
    int maxProfit(vector<int> &prices, int k = 1) //k=1
    {
        int min = prices[0];
        int maxProfit = 0;
        //记录i之前的最小值 然后用当前值减去该最小值获取最大差值
        for (int i = 1; i < prices.szie(); ++i)
        {
            if (prices[i] > min)
            {
                maxProfit = max(maxProfit, prices[i] - min);
            }
            else
            {
                min = prices[i];
            }
        }
    }
    int maxProfit(vector<int> &prices, int k = 1) //k=1
    {
        //状态转移方程很重要
        int dp_i_0 = 0, dp_i_1 = INT_MIN;
        //
        for (int i = 0; i < prices.size(); i++)
        {
            //当前的dp           上一个的dp
            //今天没有   昨天没有  昨天有然后今天卖出去了
            dp_i_0 = max(dp_i_0, dp_i_1 + prices[i]);
            //今天有股票 昨天有股票  昨天没有股票但是今天买了一支股票，因为只可以交易一次
            //所以
            dp_i_1 = max(dp_i_1, -prices[i]);
        }
        return dp_i_0;
    }
    /**
     * 想下给定的数组是怎么加入到动态转移方程的呢。
     * dp[i][k] 表示玩家在第k天 状态为i时的最大利润 设计一个算法来计算你可以获取的最大利润
     * 
     *                              前一天有股票但是今天卖出去了 所以利润要加上今天的股票价格
     * dp[0][k] = max(dp[0][k-1], dp[1][k-1] + prices[k]);
     * dp[1][k] = max(dp[1][k-1], dp[0][k-1] - prices[k]);
     *                              前一天没有股票但是今天买了一支股票。所以总利润要减去今天的股票价格
     *dp[2][k]  二维dp数组
     * 持有/非持有 1 2 3 4 5 6 7 8  
     *    0
     *    1
    */
    //这个交易次数不限的话，那就是所有插值的最大值呢。
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
        {   //第二次交易没有 前一天没有, 前一天有 今天卖出
            dp_i2_0 = max(dp_i2_0, dp_i2_1 + prices[i]);//前一天有 然后卖出去了
            //第二次交易持有，前一次持有第一次持有， 前一次没有 今天买了一只股票
            dp_i2_1 = max(dp_i1_1, dp_i2_0 - prices[i]); //前一次没有 今天买了一只股票，，
           
            //第一次交易没有 之前没有  卖出股票增加利润
            dp_i1_0 = max(dp_i1_0, dp_i1_1 + prices[i]); //这个dp_i_0会被更新
            //第一次交易持有  之前持有 第一次交易之前没有然后买入股票扣除利润
            dp_i1_1 = max(dp_i1_1, -prices[i]);
        }
        return dp_i1_0;
    }
};
//尝试说出题目内容
//尝试说出题目的内容
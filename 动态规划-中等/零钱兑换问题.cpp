// 给定不同面额的硬币 coins 和一个总金额 amount。编写一个函数来计算可以凑成总金额所需的最少的硬币个数。
// 如果没有任何一种硬币组合能组成总金额，返回 -1。

// 示例 1:

// 输入: coins = [1, 2, 5], amount = 11
// 输出: 3
// 解释: 11 = 5 + 5 + 1
// 示例 2:

// 输入: coins = [2], amount = 3
// 输出: -1

//dp[i]表示凑成i所需的最少硬币数量， 然后针对每一个i 遍历所有的coin 看是否可以更新dp[i]
//dp[i] =min(dp[i],dp[i-item]+1)for item in items;
class Solution
{
public:
    int coinChange(vector<int> &coins, int amount)
    {
        //初始化为amount + 1
        vector<int> dp(amount + 1, amount + 1);
        //凑成给定的金额 肯定是慢慢的金额从1 到amount
        //然后因为是最小 ，所以每一个位置填上最大值也是没有关系的

        dp[0] = 0; //amount为0的时候 当然是不需要硬币了

        for (int i = 0; i < dp.size(); i++)
        {
            for (auto item : coins)
            {
                if (i - item >= 0)
                    dp[i] = min(dp[i], dp[i - item] + 1);//这种写法就必须要求 dp[i] 初始化为一个很大的值 但是dp[0] = 0;
            }
        }
        return (dp[amount] == amount + 1 ? -1 : dp[amount]);
    }
};
//最少是amount + 1
//横轴是金额 纵轴是硬币数量
//离散表格的填充,离散表格的填充
/**
 * dp[money] 表示凑成i 所需的最少硬币数
 * for money 0---->amount:
 *      for coin :coins:
 *          dp[money] = min(dp[money], dp[money-coin] + 1);
 * 但是这个dp表是一维的
 * //每多增加一块钱,我们都要更新下 每多增加一块钱
*/
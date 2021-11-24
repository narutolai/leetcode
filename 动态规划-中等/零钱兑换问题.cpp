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
        vector<int> dp(amount + 1, amount + 1);
        
        dp[0] = 0;

        for (int i = 0; i < dp.size(); i++)
        {
            for (auto item : coins)
            {
                if (i - item >= 0)
                    dp[i] = min(dp[i], dp[i - item] + 1);
            }
        }
        return (dp[amount] == amount + 1 ? -1 : dp[amount]);
    }
};

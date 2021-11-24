// 给定一个由正整数组成且不存在重复数字的数组，找出和为给定目标正整数的组合的个数可重复使用

// 示例:

// nums = [1, 2, 3]
// target = 4
//这个跟凑硬币的问题是一样的
// 所有可能的组合为：
// (1, 1, 1, 1)
// (1, 1, 2)
// (1, 2, 1)
// (1, 3)
// (2, 1, 1)
// (2, 2)
// (3, 1)

// 请注意，顺序不同的序列被视作不同的组合。

// 因此输出为 7。
class Solution
{
public:
    //凑成指定数目的所有组合数
    int combinationSum4(vector<int> &nums, int target)
    {
        //初始化问题
        vector<unsigned long long> memo(target + 1, 0);
        //凑成0元 只有一种组合
        memo[0] = 1;

        //5   [1 2 3]
        //如果我现在已经有凑成5元的组合数，然后我现在面对 1,2,3三种硬币 我 就是知道凑成6 7 8 的组合数了
        for (int i = 0; i < target; i++)
        {
            for (int num : nums) //  i  num
            {
                if (i + num <= target)        //4=1 + 3
                    memo[i + num] += memo[i]; //4=2 + 2
            }
        }
        return memo[target];
    }

    //零钱兑换问题  凑成指定数目 使用最少的硬币数
    int coinChange(vector<int> &coins, int amount)
    {
        //初始化问题
        vector<int> dp(amount + 1, amount + 1);
        //凑成0元 肯定不需要硬币 那就是0了
        dp[0] = 0;
        //现在轮到dp[5]了 初始化为最多的硬币数 也就是amount ，然后 面对 1 2 3 三枚硬币 我知道 
        //dp[5] =dp[4]+1 dp[3]+1  dp[2] +1; 然后求其中最小的值 
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

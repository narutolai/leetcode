// 给定一个由正整数组成且不存在重复数字的数组，找出和为给定目标正整数的组合的个数可重复使用

// 示例:

// nums = [1, 2, 3]
// target = 4
//这个跟凑硬币的问题是一样的,可重复使用的意思就是硬币无限，既然是无限
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
//一个是求所有的组合数
//一个是求最少的拥抱数
//凑目标数和凑固定零钱都是一样
//数量无限就体现在 你的target慢慢增加的时候，
//那如果没一个硬币的数量是有限制的呢
//比如给的硬币的数量 和硬币的值，，问凑成固定数量
//怎么感觉成了背包问题，背包容量一定 ,然后固定的数量了
#if 0
01 背包问题。不超过背包总重的情况下求最大价值 0 1 的意思就是每一件物品要么放要么不放
dp[i][j]表示将前i件物品装进限重为j的背包可以获得的最大价值, 0<=i<=N, 0<=j<=W
             //i号物品不放    i号物品放入 当然前体是不超重哈
dp[i][j] = max(dp[i−1][j], dp[i−1][j−w[i]]+v[i]) // j >= w[i]
01背包问题伪代码(空间优化版)
dp[0,...,W] = 0
for i = 1,...,N
   for j = W,...,w[i] // j必须逆向枚举!!!
       dp[j] = max(dp[j], dp[j−w[i]]+v[i])
#endif

#if 0
//完全背包 就是每种物品的数量是无限的
dp[i][j]表示将前i种物品装进限重为j的背包可以获得的最大价值, 0<=i<=N, 0<=j<=W
//注意这里第二项是 dp[i][j-w[i]] + v[i]
dp[i][j] = max(dp[i−1][j], dp[i][j−w[i]]+v[i]) // j >= w[i]

// 完全背包问题思路一伪代码(空间优化版)
dp[0,...,W] = 0
for i = 1,...,N
    for j = w[i],...,W //  这里j  必须正向枚举!!!
        dp[j] = max(dp[j], dp[j−w[i]]+v[i])
#endif 

#if 0
多重背包 多重背包就是每一项物品的数量是有限的

# k为装入第i种物品的件数, k <= min(n[i], j/w[i])
dp[i][j] = max{(dp[i-1][j − k*w[i]] + k*v[i]) for every k}


#endif
// 假设你正在爬楼梯。需要 n 阶你才能到达楼顶。

// 每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？

// 注意：给定 n 是一个正整数。

// 示例 1：

// 输入： 2
// 输出： 2
// 解释： 有两种方法可以爬到楼顶。
// 1.  1 阶 + 1 阶
// 2.  2 阶 
// //
// 状态转移方程
// //dp[i]=dp[i-1]+dp[i-2]
// 为了防止越界 就用下式
//dp[i+2]=dp[i+1]+dp[i]
//答案中将空间复杂度缩减了
class Solution
{
public:
    int climbStairs(int n)
    {
        if (n <= 2)
            return n;
        int i1 = 1;
        int i2 = 2;
        for (int i = 3; i <= n; i++)
        {
            int temp = i1 + i2;
            i1 = i2;
            i2 = temp;
        }
        return i2;
    }
};

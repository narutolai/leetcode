// 最初在一个记事本上只有一个字符 'A'。你每次可以对这个记事本进行两种操作：

// Copy All (复制全部) : 你可以复制这个记事本中的所有字符(部分的复制是不允许的)。
// Paste (粘贴) : 你可以粘贴你上一次复制的字符。
// 给定一个数字 n 。你需要使用最少的操作次数，在记事本中打印出恰好 n 个 'A'。输出能够打印出 n 个 'A' 的最少操作次数。

// 示例 1:

// 输入: 3
// 输出: 3
// 解释:
// 最初, 我们只有一个字符 'A'。
// 第 1 步, 我们使用 Copy All 操作。
// 第 2 步, 我们使用 Paste 操作来获得 'AA'。
// 第 3 步, 我们使用 Paste 操作来获得 'AAA'。

class Solution
{
public:
    int max_(int x) //找到一个数的最大因子
    {
        for (int i = x - 1; i >= 1; i--)
            if (x % i == 0)
            {
                return i;
            }
        return x;
    }
    //dp[n]表示有n个A的最少操作次数
    int minSteps(int n)
    {
        vector<int> dp(n + 1);
        dp[1] = 0;
        for (int i = 2; i <= n; i++)
            if (max_(i) == 1)
                dp[i] = i; //如果一个数是质数，那所需操作数就是它本身 就拷贝原有的一个A然后一直粘贴i-1次，总操作是i次
            else
                dp[i] = dp[max_(i)] + i / max_(i); //如果是 8 那就要dp[4]+拷贝一次+复制一次 一共是 dp[4]+2次
        return dp[n];                              //如果是9那就是dp[3] 拷贝一次 +复制二次 一共是 dp[4]+3次
    }
};
//注意这道题目的关键是 只能拷贝和复制
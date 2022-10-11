// 有一个骰子模拟器会每次投掷的时候生成一个 1 到 6 的随机数。

// 不过我们在使用它时有个约束，就是使得投掷骰子时，连续 掷出数字 i 的次数不能超过 rollMax[i]（i 从 1 开始编号）。

// 现在，给你一个整数数组 rollMax 和一个整数 n，请你来计算掷 n 次骰子可得到的不同点数序列的数量。

// 假如两个序列中至少存在一个元素不同，就认为这两个序列是不同的。由于答案可能很大，所以请返回 模 10^9 + 7 之后的结果。

//  

// 示例 1：

// 输入：n = 2, rollMax = [1,1,2,2,2,3]
// 输出：34
// 解释：我们掷 2 次骰子，如果没有约束的话，共有 6 * 6 = 36 种可能的组合。但是根据 rollMax 数组，数字 1 和 2 最多连续出现一次，
// 所以不会出现序列 (1,1) 和 (2,2)。因此，最终答案是 36-2 = 34。
// 示例 2：

// 输入：n = 2, rollMax = [1,1,1,1,1,1]
// 输出：30
// 示例 3：

// 输入：n = 3, rollMax = [1,1,1,2,2,3]
// 输出：181

// dp[i][j][l]表示第i次投掷骰子，所得点数为j且连续的个数为l的种数。
class Solution
{
public:
    int dieSimulator(int n, int[] rollMax)
    {
        int[][][] dp = new int[n + 1][6][20];
        int mod = 1000000007;
        for (int i = 0; i < 6; i++)
        {
            dp[0][i][1] = 1;
        }
        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j < 6; j++)
            { //本次
                for (int k = 0; k < 6; k++)
                { //上一次
                    if (j != k)
                    {
                        for (int l = 1; l <= rollMax[k]; l++)
                        {
                            /*如果j!=k 比如 是 本次是2 上一次是1 那么 首先可以知道这个2只连续出现一次，所以他的dp[i][2][1]
                              就会等于 上一次是1的所有连续出现次数取值的累加。把1连续出现1次的，2次的。3次的(假设1最大连续次数为3)都累加起来
                              */
                            dp[i][j][1] += dp[i - 1][k][l];
                            dp[i][j][1] %= mod;
                        }
                    }
                    else
                    {
                        /*如果j==k就是说本次是2 上一次也是2,那状态转移方程就可以是 本次l+1的长度 为上次l的长度的所有累加
                         */
                        for (int l = 1; l < rollMax[k]; l++)
                        {
                            dp[i][j][l + 1] += dp[i - 1][k][l];
                            dp[i][j][l + 1] %= mod;
                        }
                    }
                }
            }
        }

        //最后结果是 到最顶层，统计每一个数以及在其连续出现次数的限定范围内的累加
        int ans = 0;
        for (int j = 0; j < 6; j++)
        {
            for (int k = 1; k <= rollMax[j]; k++)
            {
                ans += dp[n - 1][j][k];
                ans %= mod;
            }
        }
        return ans;
    }
}
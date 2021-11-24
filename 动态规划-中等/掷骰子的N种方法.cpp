// 这里有 d 个一样的骰子，每个骰子上都有 f 个面，分别标号为 1, 2, ..., f。

// 我们约定：掷骰子的得到总点数为各骰子面朝上的数字的总和。

// 如果需要掷出的总点数为 target，请你计算出有多少种不同的组合情况（所有的组合情况总共有 f^d 种），模 10^9 + 7 后返回。

//  

// 示例 1：

// 输入：d = 1, f = 6, target = 3
// 输出：1
// 示例 2：

// 输入：d = 2, f = 6, target = 7
// 输出：6

class Solution
{
public:
    int MOD = 1e9 + 7;
    int numRollsToTarget(int d, int f, int target)
    {
        int bottom = d * 1; //可以掷出的最小值 d*1
        int top = d * f;    //可以掷出的最大值 d*f
        if (target < bottom || target > top)
            return 0;
        if (d == 1 || target == bottom || target == top)
            return 1;

        vector<vector<int>> dp(d, vector<int>(target + 1, 0));

        for (int i = 1; i <= min(f, target); i++) //注意取min
            dp[0][i] = 1;
    
        for (int i = 1; i < d; i++)                                       //掷第i个骰子
            for (int j = (i + 1) * 1; j <= min(target, (i + 1) * f); j++) //前i+1个骰子可能掷出范围，注意范围  dp[i][(i+1)*1]-dp[i][(i+1)*f] 
                for (int k = 1; k <= min(f, j); k++)                      //然后针对每一个j值，我们都变化该骰子的6个面得到不同的结果666
                    dp[i][j] = (dp[i][j] + dp[i - 1][j - k]) % MOD;

        //
        //dp[i][j] =

        return dp[d - 1][target];
    }
};

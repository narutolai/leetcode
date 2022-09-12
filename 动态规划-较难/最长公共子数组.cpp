// 给两个整数数组 A 和 B ，返回两个数组中公共的、长度最长的子数组的长度。

// 示例 1:

// 输入:
// A: [1,2,3,2,1]
// B: [3,2,1,4,7]
// 输出: 3
// 解释:
// 长度最长的公共子数组是 [3, 2, 1]。
// 说明:

// 1 <= len(A), len(B) <= 1000
// 0 <= A[i], B[i] < 100

//这个和最长公共子序列是一个意思啊
class Solution
{
public:
    //这算是KMP字符串匹配吗
    int findLength(vector<int> &A, vector<int> &B)
    {
        int m = A.size(), n = B.size();
        vector<vector<int>> dp(m, vector<int>(n, 0));
        int len = 0;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (A[i] == B[j])
                {
                    dp[i][j] = ((i - 1 < 0 || j - 1 < 0) ? 0 : dp[i - 1][j - 1]) + 1;
                    // len = max(len, dp[i][j]);
                }
                else
                {
                    dp[i][j] = max(i - 1 < 0 ? 0 : dp[i - 1][j], j - 1 < 0 ?: dp[i][j - 1]);
                }
            }
        // return len;
        return dp[m - 1][n - 1];
    }
};
//遍历次数 3 2022-09-22
//直接想象下dp表的状态转移过程

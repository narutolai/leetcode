// 给定一个字符串s，找到其中最长的回文子序列。可以假设s的最大长度为1000。

// 示例 1:
// 输入:

// "bbbab"
// 输出:

// 4
// 一个可能的最长回文子序列为 "bbbb"。

// 示例 2:
// 输入:

// "cbbd"
// 输出:

// 2
// 一个可能的最长回文子序列为 "bb"。

class Solution
{
public:
    //     12a3b4c5c67b89a
    int longestPalindromeSubseq(string s)
    {
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        //对角线上都为1
        for (int i = 0; i < n; i++)
            dp[i][i] = 1;
        //从下到上 从左到右
        for (int i = n - 1; i >= 0; i--)
            for (int j = i + 1; j < n; j++)
            {
                if (s[i] == s[j])
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                else
                    dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
            }
        return dp[0][n - 1];
    }
};
//子序列不用连续 字串要连续
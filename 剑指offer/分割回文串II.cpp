给你一个字符串 s，请你将 s 分割成一些子串，使每个子串都是回文。

返回符合要求的 最少分割次数 。

 

示例 1：

输入：s = "aab"
输出：1
解释：只需一次分割就可将 s 分割成 ["aa","b"] 这样两个回文子串。
示例 2：

输入：s = "a"
输出：0
示例 3：

输入：s = "ab"
输出：1


class Solution
{
public:
	int minCut(string s)
	{
		int n = s.size();
		vector<vector<bool>> mat(n, vector<bool>(n, true));
		for (int i = n - 1; i >= 0; i--)
			for (int j = i + 1; j < n; j++)
				mat[i][j] = (s[i] == s[j]) && mat[i + 1][j - 1];

		vector<int> dp(n, INT_MAX);

		for (int i = 0; i < s.size(); i++)
		{
			if (mat[0][i])//如果0-i是回文串 那就不用管了 
				dp[i] = 0;
			else
			{
				for (int j = 0; j < i; j++)//如果0-i不是回文串 
					if (mat[j + 1][i])
						dp[i] = min(dp[i], dp[j] + 1);
			}
		}
		return dp[n - 1];
	}
};


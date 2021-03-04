22题
数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。

 

示例 1：

输入：n = 3
输出：["((()))","(()())","(())()","()(())","()()()"]
示例 2：

输入：n = 1
输出：["()"]
 

提示：

1 <= n <= 8
class Solution
{
public:
	vector<string> result;
	bool isValid(string &s)
	{
		int left = 0;
		for (auto &c : s)
		{
			if (c == '(')
				left++;
			else
			{
				left--;
				if (left < 0)
					return false;
			}
		}
		return left == 0;
	}

	void dfs(string &s, int n)
	{
		if (n == 0)
		{
			if (isValid(s))
				result.push_back(s);
			return;
		}
		s += "(";
		dfs(s, n - 1);
		s.erase(s.size() - 1, 1);
		s += ")";
		dfs(s, n - 1);
		s.erase(s.size() - 1, 1);
	}
	vector<string> generateParenthesis(int n)
	{
		string s;
		dfs(s, 2 * n);
	}
};

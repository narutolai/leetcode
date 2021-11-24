// 22题
// 数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。

//  

// 示例 1：

// 输入：n = 3
// 输出：["((()))","(()())","(())()","()(())","()()()"]
// 示例 2：

// 输入：n = 1
// 输出：["()"]
//  

// 提示：
//1 <= n <= 8
class Solution
{
public:
	vector<string> result;
	// 主要是这个函数flag为1时用来判断 最终字符是否合法，为0时用来剪枝。
	bool isValid(string &s, int size, int flag) //比如去判断 （（（
	{
		int left = 0;
		for (auto &c : s)
		{
			if (c == '(')
			{
				left++;
				if (left > size / 2)
					return false;
			}
			else
			{
				left--;
				if (left < 0)
					return false;
			}
		}
		if (flag)
		{
			return left == 0;
		}
		else
		{
			return true;
		}
	}
	void dfs(string &s, int n, int size)
	{
		if (n == 0)
		{
			if (isValid(s, size, 1)) //flag为1用来判断是否符合条件
				result.push_back(s);
			return;
		}
		
		if (isValid(s, size, 0)) //这里flag为0用来减枝
		{
			s += "(";
			dfs(s, n - 1, size);
			s.erase(s.size() - 1, 1);

			s += ")";
			dfs(s, n - 1, size);
			s.erase(s.size() - 1, 1);
		}
	}
	vector<string> generateParenthesis(int n)
	{
		string s;
		dfs(s, 2 * n, 2 * n); //遍历整个树空间 不过可以有剪枝函数。
		return result;
	}
};

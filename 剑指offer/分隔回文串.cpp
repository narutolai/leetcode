// 给你一个字符串 s，请你将 s 分割成一些子串，使每个子串都是 回文串 。返回 s 所有可能的分割方案。

// 回文串 是正着读和反着读都一样的字符串。

//  

// 示例 1：

// 输入：s = "aab"
// 输出：[["a","a","b"],["aa","b"]]
// 示例 2：

// 输入：s = "a"
// 输出：[["a"]]


class Solution
{
public:
	vector<vector<string>> result;
	//这个函数用来判断是不是回文
	bool judge(string s,int j)
	{	
		int i=0;
		while (i <= j)
		{
			if (s[i] == s[j])
			{
				i++;
				j--;
			}
			else
			{
				return false;
			}
		}
		return i > j;
	}
	
	void dfs(string s,vector<string> &temp)
	{
		if(s.size()==0)
		{
			result.push_back(temp);
			return;
		}
		for(int i=0;i<s.size();i++)//典型的回溯
		{
			if(judge(s,i))
			{
				temp.push_back(s.substr(0,i+1));
				dfs(s.substr(i+1,s.size()-i-1),temp);
				temp.pop_back();
			}
		}
	}
//遍历次数 1
	vector<vector<string>> partition(string s)
	{
		vector<string> temp;
		dfs(s,temp);
		return result;
	}
};

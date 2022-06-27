// 我一开始做的时候 以为'.'可以匹配空字符 其实是不可以的。
// 简单的说一下吧：
// 首先dp[i][j]的意思是 s[0-i]和p[0-j]的匹配情况。
// 如果要比较的字符是
// p=a.cd*f
// s=abcddf

// 如果p[j]=='.'或者p[j]==s[i]的时候,dp[i][j]的结果就看dp[i-1][j-1]的结果:
// 即:a.和ab的匹配情况看a和a,  a.c和abc的匹配情况看a.和ab。

// 如果p[j]=='*' 那就分重复0次p[j-1]或重复1次p[j-1]：
// 即：a.cd*和abcdd的匹配情况看a.c和abcdd
// 或者看 (a.cd和abcd 以及(s[i]是否等于p[j-1]))

// 凑合看吧。

class Solution
{
public:
  //这面试题是腾讯的吧 注意'.'不能是空
  bool isMatch(string s, string p)
  {
    int size = s.size();
    int psize = p.size();

    vector<vector<bool>> dp(size + 1, vector<bool>(psize + 1, false));
    dp[0][0] = true;

    for (int i = 0; i <= size; i++)
      for (int j = 1; j <= psize; j++)
      {
        if (p[j - 1] == '*')
          dp[i][j] = (i - 1 < 0 ? false : (dp[i - 1][j] && (s[i - 1] == p[j - 2] || p[j - 2] == '.'))) || dp[i][j - 2]; //
        else
          dp[i][j] = i - 1 < 0 ? false : (p[j - 1] == '.' || p[j - 1] == s[i - 1]) && dp[i - 1][j - 1];
      }
    return dp[size][psize];
  }
};
//两字符串 模式串 和 匹配串，模式串中有. 或 * 或字符
//我们需要判断，当模式串为. 或 字符等于 匹配串字符的时候
// 


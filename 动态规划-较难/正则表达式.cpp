// 我一开始做的时候 以为'.'可以匹配空字符 其实是不可以的。
// 简单的说一下吧：
// 首先dp[i][j]的意思是 s[0-i]和p[0-j]的匹配情况。
// 如果要比较的字符是
// p=a.cd*f
// s=abcddf

// 如果p[j]=='.'或者p[j]==s[i]的时候,dp[i][j]的结果就看dp[i-1][j-1]的结果:
// 即:a.和ab的匹配情况看a和a,  a.c和abc的匹配情况看a.和ab。

// 如果p[j]=='*' 则可以让p[j-1]重复一次或者让其不参与匹配：
// 即：a.cd*和abcdd的匹配情况看a.c和abcdd
// 或者看 (a.cd和abcd 以及(s[i]是否等于p[j-1]))
//注意 '.'是可以替换成字符的,但是'*' 是用来
//	匹配前面的子表达式零次或多次。例如，zo* 能匹配 "z" ,"zo","zoo"。* 等价于{0,}。
// 题目保证每次出现字符 * 时，前面都匹配到有效的字符

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
    //空的字符和空的模式串肯定是true的,但是
    //不需要初始化 因为.不能匹配空字符串 这样i =0 的那一行 就都是false了除了dp[0][0]
    for (int i = 0; i <= size; i++)
      for (int j = 1; j <= psize; j++)
      {
        if (p[j - 1] == '*')   //  让*前的数出现一次参与当前匹配所以是i-1,j  让*前的数消失 不匹配 i,j-2    
          dp[i][j] = (i - 1 < 0 ? false : (dp[i - 1][j] && (s[i - 1] == p[j - 2] || p[j - 2] == '.'))) || dp[i][j - 2]; //这里不要判断j-2小于0
        else
          dp[i][j] = i - 1 < 0 ? false : (p[j - 1] == '.' || p[j - 1] == s[i - 1]) && dp[i - 1][j - 1];
      }
    return dp[size][psize];
  }
};
//遍历次数 4
// * 是只是挂件
//两字符串 模式串 和 匹配串，模式串中有. 或 * 或字符
//我们需要判断，当模式串为. 或 字符等于 匹配串字符的时候
//我懂了 我终于懂了!!!
//注意dp[0][0] = true;
//重要的是状态转移方程！！！！
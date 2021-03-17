给定一个字符串 s 和一个字符串 t ，计算在 s 的子序列中 t 出现的个数。

字符串的一个 子序列 是指，通过删除一些（也可以不删除）字符且不干扰剩余字符相对位置所组成的新字符串。（例如，"ACE" 是 "ABCDE" 的一个子序列，而 "AEC" 不是）

题目数据保证答案符合 32 位带符号整数范围。

 

示例 1：

输入：s = "rabbbit", t = "rabbit"
输出：3
解释：
如下图所示, 有 3 种可以从 s 中得到 "rabbit" 的方案。
(上箭头符号 ^ 表示选取的字母)


题目是问 s[:i]里边有几个t[:j]。
当 s[i]!=t[j]的时候 s[:i]里的t[:j]的个数肯定和s[:i-1]一样嘛
比如 aabc里a的个数 肯定是和aab里的a的个数一样，因为c不等于a。

当 s[i]=t[j]的时候 s[:i]里的t[:j]的个数除了要加上s[:i-1]里t[:j]的量 还要加上s[:i-1]里t[:j-1]的量，
比如babc里bc的个数 就会等于bab里bc的个数(0) 再加上bab里b的个数(2)。
为什么还要加上bab里b的个数，因为bab里有两个b的话 就可以和c组成两个bc了。
懂了吧！！！因为bab里有两个b，所以babc里肯定就有两个bc呀！！！！是不是瓜娃子！！！
  b a b c 
b 1 1 2 2
c 0 0 0 2






class Solution {
public:
    int numDistinct(string s, string t) {
        int m=t.size();
        int n=s.size();
        vector<vector<long>>dp(m+1,vector<long>(n+1));
        for(int i=0;i<=n;i++)dp[0][i]=1;
        for(int i=1;i<=m;i++)dp[i][0]=0;
        //想出这个dp很重要真的，，，然后就是初始化的注意
        for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++){
            if(t[i-1]==s[j-1])
                dp[i][j]=dp[i-1][j-1]+dp[i][j-1];
            else dp[i][j]=dp[i][j-1];
        }
        return dp[m][n];
    }
};

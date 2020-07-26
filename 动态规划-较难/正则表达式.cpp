class Solution {
public:
    //这面试题是腾讯的吧 注意'.'不能是空
    bool isMatch(string s, string p) {
       int size=s.size();
       int psize=p.size();

        vector<vector<bool>> dp(size+1,vector<bool>(psize+1,false));
        dp[0][0]=true;
       
       for(int i=0;i<=size;i++)
       for(int j=1;j<=psize;j++)
       {
          if(p[j-1]=='*')
            dp[i][j]= (i-1<0?false:(dp[i-1][j]&&(s[i-1]==p[j-2]||p[j-2]=='.')))||dp[i][j-2];
          else
            dp[i][j]=i-1<0?false:(p[j-1]=='.'||p[j-1]==s[i-1])&&dp[i-1][j-1];
       } 
    return dp[size][psize];
    }
};


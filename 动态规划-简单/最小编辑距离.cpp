//s1 转化成s2所用的最小的操作数
class Solution
{
public:                                    //s1->s2的最小编辑距离
    int minDdistance(string s1, string s2) //这样的空串是要考虑到的
    {
        int s1size = s1.size(), s2size = s2.size();
        vector<vector<int>> dp(s1size + 1, vector<int>(s2size + 1, 0));

        for (int i = 1; i <= s2size; i++)
            dp[0][i] = i;
        for (int j = 1; j <= s1size; j++)
            dp[j][0] = j;

        for (int i = 1; i <= s1size; i++)
            for (int j = 1; j <= s2size; j++)
            {   
                //字符相等 什么都不需要做
                if (s1[i - 1] == s2[j - 1])
                {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else
                {   //否则的话三者最小
                    dp[i][j] = min(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]) + 1;
                }
            }
        return dp[s1size][s2size];
    }
};

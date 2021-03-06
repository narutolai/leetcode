在计算机界中，我们总是追求用有限的资源获取最大的收益。
现在，假设你分别支配着 m 个 0 和 n 个 1。另外，还有一个仅包含 0 和 1 字符串的数组。
你的任务是使用给定的 m 个 0 和 n 个 1 ，找到能拼出存在于数组中的字符串的最大数量。每个 0 和 1 至多被使用一次。
注意:

给定 0 和 1 的数量都不会超过 100。
给定字符串数组的长度不会超过 600。
示例 1:

输入: Array = {"10", "0001", "111001", "1", "0"}, m = 5, n = 3
输出: 4

解释: 总共 4 个字符串可以通过 5 个 0 和 3 个 1 拼出，即 "10","0001","1","0" 。
示例 2:

输入: Array = {"10", "0", "1"}, m = 1, n = 1
输出: 2

解释: 你可以拼出 "10"，但之后就没有剩余数字了。更好的选择是拼出 "0" 和 "1" 。

//其实这也是0-1背包问题的变种，背包容量就是0或者1的个数，然后每个字符串有一定的体积，我们要做的就是装尽可能多的物品

class Solution {
public://二维0-1背包问题
    //返回当前字符串的0和1的个数。
     vector<int> count(string s)
     {
         vector<int> count_(2);
         for(auto c:s)
         {
             count_[c-'0']++;
         }
         return count_;
     }
    int findMaxForm(vector<string>& strs, int m, int n) {
        vector<vector<int>> dp(m+1,vector<int>(n+1,0));
        dp[0][0]=0;
        for(auto s:strs)
        {     
            vector<int> temp=count(s);//返回当前字符串的0和1的个数
            for(int zeros=m;zeros>=temp[0];zeros--)
                for(int ones=n;ones>=temp[1];ones--)
                {
                dp[zeros][ones]=max(dp[zeros][ones],1+dp[zeros-temp[0]][ones-temp[1]]);
                }
        }
        return dp[m][n];
    }
};

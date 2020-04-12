给你一个整数数组 arr 和一个整数 difference，请你找出 arr 中所有相邻元素之间的差等于给定 difference 的等差子序列，并返回其中最长的等差子序列的长度。

 

示例 1：

输入：arr = [1,2,3,4], difference = 1
输出：4
解释：最长的等差子序列是 [1,2,3,4]。
示例 2：

输入：arr = [1,3,5,7], difference = 1
输出：1
解释：最长的等差子序列是任意单个元素。
示例 3：

输入：arr = [1,5,7,8,5,3,4,2,1], difference = -2
输出：4
解释：最长的等差子序列是 [7,5,3,1]。

class Solution {
public:
//超时
    int longestSubsequence(vector<int>& arr, int difference) {
      /*  int m=arr.size();
        vector<int> dp(m,1);
        int max_=1;
        for(int i=1;i<m;i++)
        for(int j=0;j<i;j++)
        if(arr[i]-arr[j]==difference)
       { dp[i]=max(dp[i],dp[j]+1);
        max_=max(max_,dp[i]);
       }
       return max_;
       */
       //map要排序 unorder_map不要排序
    unordered_map<int,int>m;
    int ans = 0;
    for(auto x: arr) 
       {    
            ans = max(ans,m[x-difference] + 1);
            m[x]=m[x-difference]+1;
       }
    return ans;
}
    
};

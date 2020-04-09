一个有名的按摩师会收到源源不断的预约请求，每个预约都可以选择接或不接。
在每次预约服务之间要有休息时间，因此她不能接受相邻的预约。
给定一个预约请求序列，替按摩师找到最优的预约集合（总预约时间最长），返回总的分钟数。

//这个跟强盗打劫问题是一个意思吧
/*
状态转移方程 抢或者不抢的问题
      dp[i+2]=max(dp[i]+nums[i],dp[i+1]);


*/
class Solution {
public:
    int massage(vector<int>& nums) {
        //这不是强盗打劫问题吗
        
        int size=nums.size();
        vector<int>dp(size+2,0);
        if(nums.size()==0) return 0;
        int max_=INT_MIN;
        //
        //数组访问越界怎么办  增长数组范围
        for(int i=0;i<nums.size();i++)
        {
            dp[i+2]=max(dp[i]+nums[i],dp[i+1]);
            max_=max(max_,dp[i+2]);
        }
        return max_;
    }
};


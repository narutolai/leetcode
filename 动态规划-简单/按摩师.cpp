// 一个有名的按摩师会收到源源不断的预约请求，每个预约都可以选择接或不接。
// 在每次预约服务之间要有休息时间，因此她不能接受相邻的预约。
// 给定一个预约请求序列，替按摩师找到最优的预约集合（总预约时间最长），返回总的分钟数。

//这个跟强盗打劫问题是一个意思吧
/*
状态转移方程 抢或者不抢的问题
      dp[i+2]=max(dp[i]+nums[i],dp[i+1]);


*/
class Solution
{
public:
    int massage(vector<int> &nums)
    {
        //感觉好多问题  其实不需要增加范围 但是呢 空间换时间 空间换时间，
        int size = nums.size(); //
        vector<int> dp(nums.size());
        int maxnum = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            dp[i] = max((i - 2 < 0 ? 0 : dp[i - 2]) + nums[i], i - 1 < 0 ? 0 : dp[i - 1]);
            maxnum = max(dp[i], maxnum);
        }
        return maxnum;
        return max_;
    }
};

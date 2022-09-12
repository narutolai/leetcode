/*
输入一个整型数组，数组里有正数也有负数。数组中的一个或连续多个整数组成一个子数组。求所有子数组的和的最大值。

要求时间复杂度为O(n)。

注意这里要求数必须是连续的

解答：
状态定义：
       dp[i]表示以num[i]结尾的最大连续子数组的和
转移方程：
       dp[i]=dp[i-1]+num[i] dp[i-1]>0     //加上一个正数总是可以使当前总和最大，不论当前num[i]是大于0还是小于0
       dp[i]=num[i]         dp[i-1]<0     //但如果是负数 那么当前总和最大就是当前num[i]了，不论num[i]大于0还是小于0
//没见过判断条件是前一个dp[i]的
时间复杂度O(n)
空间复杂度可以降至O(1)
*/

class Solution
{
public:
    int maxSubArray(vector<int> &nums)
    {
        //这个必须是连续的
        int maxnum = nums[0];
        for (int i = 1; i < nums.size(); i++)
        {
            //前一个数大于0就修改否则就不要修改这个数
            if (nums[i - 1] > 0)
                nums[i] += nums[i - 1];
            maxnum = max(maxnum, nums[i]);
        }
        return maxnum;
    }
};
//遍历次数2
//如果num[1] < 0 num[2] 还会加上num[i]吗 肯定不会 这只会让以2结尾的子数组和变小。
//连续子数组的最大和问题
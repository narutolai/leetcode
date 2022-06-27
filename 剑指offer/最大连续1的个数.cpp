// 给定一个二进制数组， 计算其中最大连续 1 的个数。

//  

// 示例：

// 输入：[1,1,0,1,1,1]
// 输出：3
// 解释：开头的两位和最后的三位都是连续 1 ，所以最大连续 1 的个数是 3.

// 滑动窗口
class Solution
{
public:
    int findMaxConsecutiveOnes(vector<int> &nums)
    {
        int res = 0, left = 0, right = 0;
        int n = nums.size();
        while (right < n)
        {
            if (nums[right])
            {
                ++right;
            }
            else
            {
                left = ++right;
            }
            res = max(res, right - left);
        }
        return res;
    }
};
//动态规划
class Solution
{
public:
    int findMaxConsecutiveOnes(vector<int> &nums)
    {
        int count = 0;
        int maxone = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            //dp[i]=(nums[i]==1)?(i-1<0?1:dp[i-1]+1):0;
            //为什么要去判断i-1<0?
         // count = nums[i] == 1 ? (i - 1 < 0 ? 1 : count + 1) : 0;
            count = nums[i] == 1 ? count + 1 : 0;
            maxone = max(maxone, count);
        }
        return maxone;
    }
};
//因为并不需要知道每一个数的连续1的个数  所以不需要用O(N)的空间复杂度 只需要O(1)的空间复杂度

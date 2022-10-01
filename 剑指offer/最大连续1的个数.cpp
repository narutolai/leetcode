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
        int continueOne = 0;
        int maxContinueOne= 0;
        for (int i = 0; i < nums.size(); i++)
        {
            continueOne = nums[i] == 1 ? continueOne + 1 : 0;
            maxContinueOne = max(maxContinueOne, continueOne);
        }
        return maxContinueOne;
    }
};
//因为并不需要知道每一个数的连续1的个数  所以不需要用O(N)的空间复杂度 只需要O(1)的空间复杂度
//一遍遍历 count = nums[i] == 1?count+1:0;
//遍历次数 2
//2022-09-30 17:18

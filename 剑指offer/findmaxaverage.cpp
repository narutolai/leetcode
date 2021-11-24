// https://leetcode-cn.com/problems/maximum-average-subarray-i/
// 给定 n 个整数，找出平均数最大且长度为 k 的连续子数组，并输出该最大平均数。

//  

// 示例：

// 输入：[1,12,-5,-6,50,3], k = 4
// 输出：12.75
// 解释：最大平均数 (12-5-6+50)/4 = 51/4 = 12.75
//  

// 提示：

// 1 <= k <= n <= 30,000。
// 所给数据范围 [-10,000，10,000]。

class Solution
{
public:
    double findMaxAverage(vector<int> &nums, int k)
    {
        if (nums.size() <= k)
            return (double)accumulate(nums.begin(), nums.end(), 0) / (int)nums.size();
        vector<int>::iterator iter = nums.begin();
        //注意这个题目返回的是浮点数
        //每次都加数组内k的值会超时的
        double beginsum = accumulate(iter, iter + k, 0);
        double maxaverage = beginsum / k;
        while ((iter + k) != nums.end())//其实还是感觉没有这必要的啊
        {
            iter++;
            beginsum += *(iter + k - 1);
            beginsum -= *(iter - 1);
            double average = beginsum / k;
            maxaverage = average > maxaverage ? average : maxaverage;
        }
        return maxaverage;
    }
};

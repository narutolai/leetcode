// 给定一个未排序的整数数组，找到最长递增子序列的个数。

// 示例 1:

// 输入: [1,3,5,4,7]
// 输出: 2
// 解释: 有两个最长递增子序列，分别是 [1, 3, 4, 7] 和[1, 3, 5, 7]。
// 示例 2:

// 输入: [2,2,2,2,2]
// 输出: 5
// 解释: 最长递增子序列的长度是1，并且存在5个子序列的长度为1，因此输出5。

// 如果只是找到最长递增子序列可以轻易知道
// dp[i]=max(dp[i],dp[j]+1) for j in [0-i)
// for(int i=1;i<size;i++)
// for(int j=0;j<i;j++)
// if(num[i]>num[j])
// dp[i]=max(dp[i],dp[j]+1)
// 不过这一题我们要找出所有的最长子序列
// 方法一：动态规划
// 算法：

// 假设对于以 nums[i] 结尾的序列，我们知道最长序列的长度 length[i]，以及具有该长度的序列的 count[i]。
// 对于每一个 i<j 和一个 A[i]<A[j]，我们可以将一个 A[j] 附加到以 A[i] 结尾的最长子序列上。
// 如果这些序列比 length[j] 长，那么我们就知道我们有count[i] 个长度为 length 的序列。如果这些序列的长度与 length[j] 相等，
// 那么我们就知道现在有 count[i] 个额外的序列（即 count[j]+=count[i]）。
class Solution
{
public:
    int findNumberOfLIS(vector<int> &nums)
    {
        if (!nums.size())
            return 0;
        int n = nums.size();
        vector<int> count(n, 1);
        int max_ = INT_MIN;
        vector<int> dp(n, 1);

        for (int i = 0; i < n; i++)
        {
            dp[i] = 1;
            for (int j = 0; j < i; j++)
            {
                if (nums[i] > nums[j])//如果 num[i]>num[j] 
                {
                    if (dp[j] + 1 > dp[i])
                    {
                        dp[i] = dp[j] + 1;
                        count[i] = count[j];
                    }
                    else if (dp[j] + 1 == dp[i])
                        count[i] += count[j];
                }
            }
            max_ = max(max_, dp[i]);
        }

        int result = 0;
        for (int i = 0; i < n; i++)
        {
            if (dp[i] == max_)
                result += count[i];
        }

        return result;
    }
};
//遍历次数 1
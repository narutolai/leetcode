// 给出一个由无重复的正整数组成的集合，找出其中最大的整除子集，子集中任意一对 (Si，Sj) 都要满足：Si % Sj = 0 或 Sj % Si = 0。

// 如果有多个目标子集，返回其中任何一个均可。

//  

// 示例 1:

// 输入: [1,2,3]
// 输出: [1,2] (当然, [1,3] 也正确)
// 示例 2:

// 输入: [1,2,4,8]
// 输出: [1,2,4,8]

// 输入：[2,3,4,8,9]
// 输出：[2,4,8]

class Solution
{
public:
    //最长子序列像不像。
    vector<int> largestDivisibleSubset(vector<int> &nums)
    {
        int size = nums.size();
        if (size < 1)
            return {};

        sort(nums.begin(), nums.end());

        //以nums[i]结尾的最大整除子集的长度 注意是已经排序的nums。
        vector<int> dp(size, 1);
        //该数的前一个数的下标
        vector<int> pre(size, -1);

        int maxval = 1;
        int maxind = 0;

        //先排个序还是有好处的啊
        // [2,3,4,8,9]
        for (int i = 1; i < size; i++)
            for (int j = i - 1; j >= 0; j--)
            {
                if (nums[i] % nums[j] == 0 && dp[j] + 1 > dp[i])//为什么是+1大于dp[i]啊???????
                {           //如果dp[j] + 1 = dp[i] 那也就没必要赋值了对吧，
                    dp[i] = dp[j] + 1;
                    pre[i] = j;
                }

                if (dp[i] > maxval)
                {
                    maxval = dp[i];
                    maxind = i;
                }
            }
        vector<int> res;
        
        for (int i = maxind; i != -1; i = pre[i])
            res.insert(res.begin(), nums[i]);
        return res;
    }
};

//没有明白哦我擦
//没有明白为什么是
//遍历次数 3  没懂哦
//没懂我擦

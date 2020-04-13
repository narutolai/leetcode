给你一个整数数组 nums，请你找出并返回能被三整除的元素最大和。

示例 1：

输入：nums = [3,6,5,1,8]
输出：18
解释：选出数字 3, 6, 1 和 8，它们的和是 18（可被 3 整除的最大和）。
示例 2：

输入：nums = [4]
输出：0
解释：4 不能被 3 整除，所以无法选出数字，返回 0。
示例 3：

输入：nums = [1,2,3,4,4]
输出：12
解释：选出数字 1, 3, 4 以及 4，它们的和是 12（可被 3 整除的最大和）。

class Solution {
public:
    int maxSumDivThree(vector<int>& nums) {
        int dp[3] = {0, 0, 0};
        
        for (int i = 0; i < nums.size(); ++i) {
            int mod = nums[i] % 3;

            int a = dp[(3 + 0 - mod) % 3];
            int b = dp[(3 + 1 - mod) % 3];
            int c = dp[(3 + 2 - mod) % 3];
            
            //如果mod==0那么 这个a就是之前的dp[0]
            if (a || mod == 0) dp[0] = std::max(dp[0], a + nums[i]); 
            //如果mod==1那么 这个b就是之前的dp[0]
            if (b || mod == 1) dp[1] = std::max(dp[1], b + nums[i]);
            //如果mod==2,那么这个c也是之前的dp[0]
            if (c || mod == 2) dp[2] = std::max(dp[2], c + nums[i]);
        }
        return dp[0];
    }
};


// 数组的每个索引做为一个阶梯，第 i个阶梯对应着一个非负数的体力花费值 cost[i](索引从0开始)。

// 每当你爬上一个阶梯你都要花费对应的体力花费值，然后你可以选择继续爬一个阶梯或者爬两个阶梯。

// 您需要找到达到楼层顶部的最低花费。在开始时，你可以选择从索引为 0 或 1 的元素作为初始阶梯。

// 示例 1:

// 输入: cost = [10, 15, 20]
// 输出: 15
// 解释: 最低花费是从cost[1]开始，然后走两步即可到阶梯顶，一共花费15。
//  示例 2:

// 输入: cost = [1, 100, 1, 1, 1, 100, 1, 1, 100, 1]
// 输出: 6
// 解释: 最低花费方式是从cost[0]开始，逐个经过那些1，跳过cost[3]，一共花费6。
// 注意：

//要么从n-1到达台阶n,要么从n-2到达台阶n，既然是最小花费肯定是选择最小的花费了
//空间复杂度可以缩减
class Solution
{
public:
    int minCostClimbingStairs(vector<int> &cost)
    {
        int n = cost.size();
        vector<int> dp(n, 0);
        dp[0] = cost[0];
        dp[1] = cost[1];
        for (int i = 2; i < n; i++)
            dp[i] = min(dp[i - 1], dp[i - 2]) + cost[i];
        //           [0,1,2,3]
        //我知道为什么[10,15,20,0]是15了直接从15 蹦到楼顶啊 没错  没毛病

        return min(dp[n - 1], dp[n - 2]);
    }
};
//这道题目有问题啊，数组最后边要加上一个0 这题目有问题真的。。。。
class Solution
{
public:
    int minCostClimbingStairs(vector<int> &cost)
    {
        //这里在尾部压入0
        cost.push_back(0);
        int n = cost.size();
        vector<int> dp(n, 0);
        dp[0] = cost[0];
        dp[1] = cost[1];
        for (int i = 2; i < n; i++)
            dp[i] = min(dp[i - 1], dp[i - 2]) + cost[i];
        //           [0,1,2,3]
        //我知道为什么[10,15,20,0]是15了直接从15 蹦到楼顶啊 没错  没毛病
        //然后这里就可以直接返回dp[n-1]了
        return dp[n - 1];
    }
};

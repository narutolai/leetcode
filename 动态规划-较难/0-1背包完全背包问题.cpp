硬币。给定数量不限的硬币，币值为25分、10分、5分和1分，编写代码计算n分有几种表示法。(结果可能会很大，你需要将结果模上1000000007)

示例1:

输入: n = 5
输出：2
解释: 有两种方式可以凑成总金额:
5=5
5=1+1+1+1+1
示例2:

输入: n = 10
输出：4
解释: 有四种方式可以凑成总金额:
10=10
10=5+5
10=5+1+1+1+1+1
10=1+1+1+1+1+1+1+1+1+1

你可以假设：
0 <= n (总金额) <= 1000000
注意题目问的是凑成某个数的组合数
还有问最小硬币问题
根本就是到达硬币数量是否可以无限取
背包问题其实是问的最大价值
0-1背包： dp[ i+1 ][ j ] = max ( dp[ i ][ j ], dp[ i ][ j - ci ] + wi )；
完全背包：dp[ i+1 ][ j ] = max ( dp[ i ][ j ], dp[ i +1 ][ j - ci ] + wi )；

class Solution {
public:
    int waysToChange(int n) {
            int mod=1e9+7;
        int item[4]={1,5,10,25};
        vector<int> dp(n+1);
        dp[0]=1;
     for(int ic:item)  //针对每一个硬币 
     for(int i=ic;i<=n;i++)//从最小值 到目标值 更新dp[i]  属于完全背包问题。
     {                      //如果是0-1背包 那就是从最大到最小
        dp[i]=dp[i]+dp[i-ic]%mod;
     }
    return dp[n]%mod;
    }
};

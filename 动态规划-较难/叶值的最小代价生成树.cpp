给你一个正整数数组 arr，考虑所有满足以下条件的二叉树：

每个节点都有 0 个或是 2 个子节点。
数组 arr 中的值与树的中序遍历中每个叶节点的值一一对应。（知识回顾：如果一个节点有 0 个子节点，那么该节点为叶节点。）
每个非叶节点的值等于其左子树和右子树中叶节点的最大值的乘积。
在所有这样的二叉树中，返回每个非叶节点的值的最小可能总和。这个和的值是一个 32 位整数。

示例：

输入：arr = [6,2,4]
输出：32
解释：
有两种可能的树，第一种的非叶节点的总和为 36，第二种非叶节点的总和为 32。

    24            24
   /  \          /  \
  12   4        6    8
 /  \               / \
6    2             2   4

//这道题的核心是:
//要知道中序遍历就决定了arr数组（0...n-1）里的第k位元素的所有左边元素（包括它自己）都在左子树里，而其右边元素都在右子树里
//而此时左右两边子树分别选出最大值的乘积就是此时的根，也就是题目中说的非叶节点
//所以我们可以假定从i到j位，最小和可能是：此刻k位左右两边元素中最大值的乘积 + 子问题k左边(i,k)的最小值 + 子问题k位右边(k+1,j)的最小值
//即：dp[i][j]=min(dp[i][j], dp[i][k] + dp[k+1][j] + max[i][k]*max[k+1][j])
//这道题跟leetcode1039一个套路
//求arr从i到j之间的元素最大值, 保存在max[i][j]中
//这道题i和j是可以相等的

class Solution {
public:

    int mctFromLeafValues(vector<int>& arr) {
        //dp[i][j]=min(dp[i][j], dp[i][k] + dp[k+1][j] + max[i][k]*max[k+1][j]) 
         int n=arr.size();
         vector<vector<int>> max_(n,vector<int>(n,0));
         for(int i=0;i<n;i++)
         {
             int maxvalue=arr[i];
             for(int j=i;j>=0;j--)
            { 
                maxvalue=max(maxvalue,arr[j]);
                max_[i][j]=maxvalue;
            }
         }
         vector<vector<int>> dp(n,vector<int>(n,0));
         for(int i=0;i<n;i++)
         for(int j=i;j>=0;j--)
         {  int min_=INT_MAX;
                for(int k=j;k<i;k++)
              {  min_=min(min_,dp[j][k]+dp[k+1][i]+max_[j][k]*max_[k+1][i]);
                dp[j][i]=min_;
              }
         }
        return dp[0][n-1];
    }
};
//还有一种方法是单调栈 没看

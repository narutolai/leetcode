给定一个只包含正整数的非空数组。是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。

注意:

每个数组中的元素不会超过 100
数组的大小不会超过 200
示例 1:

输入: [1, 5, 11, 5]

输出: true

解释: 数组可以分割成 [1, 5, 5] 和 [11].

//就是说数组中某些元素的累加和是否可以到达一半，索引从0开始 深度优先搜索

//递归--->带备忘录的递归--->动态规划
class Solution {
public:
    bool dfs(int target,vector<int>& nums,int j)
    {
        if(target==0)return true;
        if(j==nums.size()) return false; //遍历完所有项目
        if(target<0) return false;       
        return dfs(target-nums[j],nums,j+1)||dfs(target,nums,j+1);//减或不减跳过j项
    }
    bool canPartition(vector<int>& nums) {
        int sum=accumulate(nums.begin(),nums.end(),0);//数组总和
         sort(nums.rbegin(),nums.rend());              //数组排序
         int target=sum/2;                              
         if(sum%2==1)
             return false;
         if(nums[0]>target)
             return false;
         if(nums[0]==target)
             return true;
         return dfs(target,nums,0);
    }
};
//动态规划的解法 0-1背包问题
/*
事实上，这是一个典型的“动态规划”问题，并且它的“原形”是“0-1 背包问题”。
使用“动态规划”解决问题的思路是“以空间换时间”，“规划”这个词在英文中就是“填表格”的意思，代码执行的过程，也可以称之为“填表格”。
“动态规划”的方法可以认为是为我们提供了一个思考问题的方向，我们不是直接面对问题求解，
而是去找原始问题（或者说和原始问题相关的问题）的最开始的样子，通过“状态转移方程”（这里没法再解释了，可以结合下文理解）记录下每一步求解的结果，直到最终问题解决。
而直接面对问题求解，就是我们熟悉的“递归”方法，由于有大量重复子问题，我们就需要加缓存，这叫“记忆化递归”，这里就不给参考代码了，感兴趣的朋友可以自己写一下，比较一下它们两种思考方式的不同之处和优缺点。
做这道题需要做这样一个等价转换：是否可以从这个数组中挑选出一些正整数，使得这些数的和等于整个数组元素的和的一半。
前提条件是：数组的和一定得是偶数，即数组的和一定得被 2 整除，这一点是特判
*/
/*
    0 1 2 3 4 5 6 7 8 9 10 11       逆序
1   T T                             dp[1]=dp[1]||dp[0] =true
5   T         T T                   dp[6]=dp[6]||dp[6-5]=dp[1]=true   dp[5]=dp[5]||dp[5-5]=dp[0]=true
11  T                      T        dp[11]=dp[11]||dp[11-11]=dp[0]=true
5   T                      T        dp[11]=dp[11]||dp[11-5]=dp[6]=true
*/
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum=accumulate(nums.begin(),nums.end(),0);//数组总和
        int target=sum/2;                              
        if(sum%2==1)return false;
        if(nums[0]>target)return false;
        
        vector<int> dp(target+1,false);
        dp[0]=true;
        for(int i=0;i<nums.size();i++)
        for(int j=target;j>=nums[i];j--)
            dp[j]=dp[j]||dp[j-nums[i]];
            return dp[target];
    }
};

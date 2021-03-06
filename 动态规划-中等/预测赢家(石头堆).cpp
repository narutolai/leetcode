给定一个表示分数的非负整数数组。 玩家1从数组任意一端拿取一个分数，随后玩家2继续从剩余数组任意一端拿取分数，然后玩家1拿，……。
每次一个玩家只能拿取一个分数，分数被拿取之后不再可取。直到没有剩余分数可取时游戏结束。最终获得分数总和最多的玩家获胜。
给定一个表示分数的数组，预测玩家1是否会成为赢家。你可以假设每个玩家的玩法都会使他的分数最大化。

示例 1:

输入: [1, 5, 2]
输出: False
解释: 一开始，玩家1可以从1和2中进行选择。
如果他选择2（或者1），那么玩家2可以从1（或者2）和5中进行选择。如果玩家2选择了5，那么玩家1则只剩下1（或者2）可选。
所以，玩家1的最终分数为 1 + 2 = 3，而玩家2为 5。
因此，玩家1永远不会成为赢家，返回 False。
示例 2:

输入: [1, 5, 233, 7]
输出: True
解释: 玩家1一开始选择1。然后玩家2必须从5和7中进行选择。无论玩家2选择了哪个，玩家1都可以选择233。
最终，玩家1（234分）比玩家2（12分）获得更多的分数，所以返回 True，表示玩家1可以成为赢家。

class Solution {

//不外乎是一道动态规划
//搞清楚递增的状态是什么 
//已经在每一个状态可能的选择，
//状态和状态之间是怎么联系的

public:
    bool PredictTheWinner(vector<int>& nums) {
    int m=nums.size();
    if(m<3) return true;
    vector<vector<pair<int,int>>> dp(m,vector<pair<int,int>>(m));
    
    //初始化对角线上元素
    for(int i=0;i<m;i++)
        dp[i][i]={nums[i],0};
    
    for(int k=1;k<m;k++)
    for(int i=0;i+k<m;i++)
    {
        int j=i+k; 
        //   i ,i+1......j-1,j
        int left=nums[i]+dp[i+1][j].second;  //面对 i,j先手i 则 i+1,j的后手
        int right=nums[j]+dp[i][j-1].second;
        if(left>right)
            dp[i][j]={left,dp[i+1][j].first};
        else 
            dp[i][j]={right,dp[i][j-1].first};
    }
    return dp[0][m-1].first>=dp[0][m-1].second;
    }
};

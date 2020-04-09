一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为“Start” ）。

机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为“Finish”）。

现在考虑网格中有障碍物。那么从左上角到右下角将会有多少条不同的路径？


到达一个网格的方法总数是 从上方来的方法数和从左方来的方法数的总和

dp[i][j]=dp[i-1][j]+dp[i][j-1];


class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        if(obstacleGrid.empty()||obstacleGrid[0].empty())return 0;

        int m=obstacleGrid.size(),n=obstacleGrid[0].size();

        vector<vector<long>> dp(m,vector<long>(n,0));

        for(int i=0;i<m;i++)
        for(int j=0;j<n;j++){
            if(obstacleGrid[i][j]==1) dp[i][j]=0;
            else{
               if(i==0 && j==0) dp[i][j]=1;            //原点处
               else if(i==0) dp[i][j]=dp[i][j-1];      //第一行
               else if(j==0) dp[i][j]=dp[i-1][j];      //第一列
               else dp[i][j]=dp[i-1][j]+dp[i][j-1];    //其他位置
            }
        }
    return dp.back().back();
    }
};

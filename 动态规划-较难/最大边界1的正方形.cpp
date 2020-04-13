给你一个由若干 0 和 1 组成的二维网格 grid，请你找出边界全部由 1 组成的最大 正方形 子网格，并返回该子网格中的元素数量。如果不存在，则返回 0。

 

示例 1：

输入：grid = [[1,1,1],[1,0,1],[1,1,1]]
输出：9
示例 2：

输入：grid = [[1,1,0,0]]
输出：1

class Solution {
public:
    int largest1BorderedSquare(vector<vector<int>>& grid) {
    int m=grid.size();
    int n=grid[0].size();
    vector<vector<vector<int>>> dp (m,vector<vector<int>>(n,vector<int>(2,0)));
    int size=0;
    for(int i=0;i<m;i++)
    for(int j=0;j<n;j++)
   { 
       if(grid[i][j]==0)  //当前位置为0
        {
                dp[i][j][0]=0;
                dp[i][j][1]=0;
        }
        else                  //当前位置为1
        {
                dp[i][j][0]=(j-1<0?0:dp[i][j-1][0])+1;
                dp[i][j][1]=(i-1<0?0:dp[i-1][j][1])+1;
                for(int size_=min(dp[i][j][0],dp[i][j][1]);size_>=size;size_--)
                {
                if(dp[i-size_+1][j][0]>=size_&&dp[i][j-size_+1][1]>=size_)//如果该子方阵真的存在
                { 
                    size=max(size,size_);
                }
                } 
        }
      }
    return size*size;
    }
};

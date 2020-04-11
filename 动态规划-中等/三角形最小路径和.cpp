给定一个三角形，找出自顶向下的最小路径和。每一步只能移动到下一行中相邻的结点上。

例如，给定三角形：

[
     [2],
    [3,4],
   [6,5,7],
  [4,1,8,3]
]
自顶向下的最小路径和为 11（即，2 + 3 + 5 + 1 = 11）。

说明：

如果你可以只使用 O(n) 的额外空间（n 为三角形的总行数）来解决这个问题，那么你的算法会很加分。

2            2
3 4          5  6
6 5 7        11 10 13 
4 1 8 3      15 11 18 16 

dp[i][j]=min(dp[i-1][j],dp[i-1][j-1])+matrix[i][j]
很明显可以转化为一个一维数组
dp的变化形态
0 0 0 0 0
4 1 8 3
7 6 10
9 10
11

class Solution{
public:
      int minimumTotal(vector<vector<int>>& triangle)
      {
        int n=triangle.size(),dp[n+1];
        memset(dp,0,sizeof(dp));
        for(int i=n-1;i>=0;--i)
        {
            for(int j=0;j<=i;++j)  //从下往上，从左到右遍历数组
             {
                dp[j]=min(dp[j],dp[j+1])+triangle[i][j];
            }
        }
      return dp[0];
    }
**/
    }
};

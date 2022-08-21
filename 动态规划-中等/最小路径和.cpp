// 给定一个包含非负整数的 m x n 网格，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。

// 说明：每次只能向下或者向右移动一步。

// 示例:

// 输入:
// [
//   [1,3,1],
//   [1,5,1],
//   [4,2,1]
// ]
// 输出: 7
// 解释: 因为路径 1→3→1→1→1 的总和最小

class Solution
{
public:
    int minPathSum(vector<vector<int>> &grid)
    {
        int n = grid[0].size();
        int m = grid.size();
        for (int i = 1; i < n; i++)
            grid[0][i] = grid[0][i - 1] + grid[0][i]; //第一行
        for (int i = 1; i < m; i++)
            grid[i][0] = grid[i - 1][0] + grid[i][0]; //第一列 i-1<0?INT_MAX:grid[i-1][j]
            
        for (int i = 1; i < m; i++)
        {
            for (int j = 1; j < n; j++)
                grid[i][j] = min(grid[i - 1][j], grid[i][j - 1]) + grid[i][j];
        }
        return grid[m - 1][n - 1];
    }
};
//这个是二选1的情况，实际上是沃恩的一种选择而已
//而一个地方的路径都可以计算出来的。
//遍历次数 2
//有没有发现 当前问题可以有多个子问题的而来的时候，我们总是可以求最小 min() ,或最大 max(), 由或者是总数 sum()
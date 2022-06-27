// 给你一个由若干 0 和 1 组成的二维网格 grid，请你找出边界全部由 1 组成的最大正方形 子网格，并返回该子网格中的元素数量。如果不存在，则返回 0。

//  

// 示例 1：

// 输入：grid = [[1,1,1],[1,0,1],[1,1,1]]
// 输出：9
//

// 输入：grid = [[1,1,0,0]]
// 输出：1

class Solution
{
public:
    int largest1BorderedSquare(vector<vector<int>> &grid)
    {
        int m = grid.size();
        int n = grid[0].size();
        

        //dp[i][j][0/1] 表示在（i,j）处 垂直方向和水平方向上连续1的个数
        vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(2, 0)));
        int size = 0;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == 0) //当前位置为0
                {
                    dp[i][j][0] = 0;
                    dp[i][j][1] = 0;
                }
                else //当前位置为1
                {
                    dp[i][j][0] = (j - 1 < 0 ? 0 : dp[i][j - 1][0]) + 1;
                    dp[i][j][1] = (i - 1 < 0 ? 0 : dp[i - 1][j][1]) + 1;

                    //两者的最小值
                    for (int size_ = min(dp[i][j][0], dp[i][j][1]); size_ >= size; size_--)
                    {
                        if (dp[i - size_ + 1][j][0] >= size_ && dp[i][j - size_ + 1][1] >= size_) //如果该子方阵真的存在
                        {
                            size = max(size, size_);
                        }
                    }
                }
            }
        return size * size;
    }
};
//上面这道题是边界为1的正方形  边界的话 记录每一个位置向上 和向右连续1的最大个数
//这个是全1的正方形 全1取三个值中的最小值
class Solution
{
public:
    int maximalSquare(vector<vector<char>> &matrix)
    {
        int row = matrix.size();
        if (row < 1)
            return 0;
        int cols = matrix[0].size();
        //你这也算是空间换时间了
        vector<vector<int>> dp(row + 1, vector<int>(cols + 1, 0));
        int maxlength = 0;

        for (int i = 1; i <= row; i++)
            for (int j = 1; j <= cols; j++)
            {
                if (matrix[i - 1][j - 1] == '1')
                {
                    dp[i][j] = min(min(dp[i][j - 1], dp[i - 1][j]), dp[i - 1][j - 1]) + 1;
                    maxlength = max(dp[i][j], maxlength);
                }
            }
        return maxlength * maxlength;
    }
};
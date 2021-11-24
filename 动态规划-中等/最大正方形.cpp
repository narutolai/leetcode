// 在一个由 0 和 1 组成的二维矩阵内，找到只包含 1 的最大正方形，并返回其面积。

// 示例:

// 输入:

// 1 0 1 0 0
// 1 0 1 1 1
// 1 1 1 1 1
// 1 0 0 1 0

// 输出: 4

// dp[i][j]=n表示到位置i,j处为止有个边长为n*n的正方形

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

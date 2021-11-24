// 给定一个二维矩阵，计算其子矩形范围内元素的总和，该子矩阵的左上角为 (row1, col1) ，右下角为 (row2, col2)。

// 上图子矩阵左上角 (row1, col1) = (2, 1) ，右下角(row2, col2) = (4, 3)，该子矩形内元素的总和为 8。

// 示例:

// 给定 matrix = [
//   [3, 0, 1, 4, 2],
//   [5, 6, 3, 2, 1],
//   [1, 2, 0, 1, 5],
//   [4, 1, 0, 1, 7],
//   [1, 0, 3, 0, 5]
// ]

// sumRegion(2, 1, 4, 3) -> 8
// sumRegion(1, 1, 2, 2) -> 11
// sumRegion(1, 2, 2, 4) -> 12

//这个就是数列的前n项和的那个问题。
class NumMatrix
{
public: //另外创造一个二维数组缓存矩阵的和
    vector<vector<int>> sum_;
    NumMatrix(vector<vector<int>> &matrix)
    {
        if (matrix.size() == 0 || matrix[0].size() == 0)
            return;
        int m = matrix.size(), n = matrix[0].size();

        vector<vector<int>> sum(m + 1, vector<int>(n + 1));
        sum[0][0] = matrix[0][0];
        for (int i = 1; i < m; i++)
            sum[i][0] = matrix[i][0] + sum[i - 1][0];
        for (int j = 1; j < n; j++)
            sum[0][j] = matrix[0][j] + sum[0][j - 1];

        for (int i = 1; i < m; i++)
            for (int j = 1; j < n; j++)
            {
                sum[i][j] = matrix[i][j] + sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
            }
        sum_ = sum;
    }
    //难怪要预留一个位置，这里会出现负数，在矩阵左边和上边外围padding一个圈0
    int sumRegion(int row1, int col1, int row2, int col2)
    {
        if (col1 == 0 && row1 == 0)
            return sum_[row2][col2];
        else if (col1 == 0 && row1 != 0)
            return sum_[row2][col2] - sum_[row1 - 1][col2];
        else if (col1 != 0 && row1 == 0)
            return sum_[row2][col2] - sum_[row2][col1 - 1];
        else
            return sum_[row2][col2] - sum_[row2][col1 - 1] - sum_[row1 - 1][col2] + sum_[row1 - 1][col1 - 1];
    }
};

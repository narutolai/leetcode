// 编写一个高效的算法来判断 m x n 矩阵中，是否存在一个目标值。该矩阵具有如下特性：

// 每行中的整数从左到右按升序排列。
// 每行的第一个整数大于前一行的最后一个整数。
// 因为有这个特征  所以可以直接平铺开来然后使用二分搜索。

class Solution
{
public:
    bool searchMatrix(vector<vector<int>> &matrix, int target)
    {
        int m = matrix.size(), n = matrix[0].size();
        int i = 0, j = m * n - 1;

        while (i <= j)
        {
            int mid = (i + j) / 2;
            if (matrix[mid / n][mid % n] == target)
                return true;
            else if (target > matrix[mid / n][mid % n])
            {
                i = mid + 1;
            }
            else
            {
                j = mid - 1;
            }
        }
        return false;
    }
};

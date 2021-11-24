// // 给你一个 m x n 的矩阵 matrix 。如果这个矩阵是托普利茨矩阵，返回 true ；否则，返回 false 。

// // 如果矩阵上每一条由左上到右下的对角线上的元素都相同，那么这个矩阵是 托普利茨矩阵 。

// //  

// // 输入：matrix = [[1,2,3,4],
//                    [5,1,2,3],
//                    [9,5,1,2]]
// // 输出：true
// // 解释：
// // 在上述矩阵中, 其对角线为:
// // "[9]", "[5, 5]", "[1, 1, 1]", "[2, 2, 2]", "[3, 3]", "[4]"。
// // 各条对角线上的所有元素均相同, 因此答案是 True 。

class Solution
{
public:
    bool isToeplitzMatrix(vector<vector<int>> &matrix)
    {
        int m = matrix.size() - 1;
        int n = 1;
        int x, y;
        //大概是依次遍历第一列和第一行的所有元素。如果等于下一个元素就++
        while (m >= 0)
        {
            x = m, y = 0;
            int num = matrix[x][y];
            while (x + 1 < matrix.size() && y + 1 < matrix[0].size())
            {
                if (num == matrix[x + 1][y + 1])
                {
                    x++;
                    y++;
                }
                else
                {
                    return false;
                }
            }
            m--;
        }

        while (n < matrix[0].size())
        {
            x = 0, y = n;
            int num = matrix[x][y];
            while (x + 1 < matrix.size() && y + 1 < matrix[0].size())
            {
                if (num == matrix[x + 1][y + 1])
                {
                    x++;
                    y++;
                }
                else
                {
                    return false;
                }
            }
            n++;
        }
        return true;
    }
};

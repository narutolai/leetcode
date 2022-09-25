class Solution
{
public:
    vector<int> spiralOrder(vector<vector<int>> &matrix)
    {
        int left = 0, up = 0, down = matrix.size() - 1, right = down >= 0 ? matrix[0].size() - 1 : -1;
        int i = 0;
        vector<int> result;
        //可以使用这个作为条件  left<=right 以及 up<=down
        while (left <= right && up <= down)
        {
            for (i = left; i <= right; i++)
            {
                result.push_back(matrix[up][i]);
            }
            up++;
            for (i = up; i <= down; i++)
            {
                result.push_back(matrix[i][right]);
            }
            right--;
            for (i = right; i >= left && up <= down; i--) //然后就是这两个需要这样 。
            {
                result.push_back(matrix[down][i]);
            }
            down--;
            for (i = down; i >= up && left <= right; i--)
            {
                result.push_back(matrix[i][left]);
            }
            left++;
        }
        return result;
    }
};
//重新命名的话应该加一个bound后缀

class Solution
{
public:
    vector<int> spiralOrder(vector<vector<int>> &matrix)
    {
        int left = 0, up = 0, down = matrix.size() - 1, right = down >= 0 ? matrix[0].size() - 1 : -1;
        vector<int> result;
        int k = 0;
        //可以使用这个作为条件  left<=right 以及 up<=down
        while (left <= right && up <= down)
        {
            for (int i = left; i <= right; i++)
            {
                result.push_back(matrix[up][i]);
                k++;
            }
            up++;
            for (int i = up; i <= down; i++)
            {
                result.push_back(matrix[i][right]);
                k++;
            }
            right--;
            for (int i = right; i >= left && up <= down; i--) //然后就是这两个需要这样 。
            {

                result.push_back(matrix[down][i]);
                k++;
            }
            down--;
            for (int i = down; i >= up && left <= right; i--)
            {
                result.push_back(matrix[i][left]);
                k++;
            }
            left++;
        }
        return result;
    }
};

//就是python的reshape()函数

class Solution
{
public:
    vector<vector<int>> matrixReshape(vector<vector<int>> &nums, int r, int c)
    {
        int m = nums.size();
        int n = nums[0].size();
        if (m * n != r * c)
            return nums;

        vector<vector<int>> numsnew(r, vector<int>(c, 0));

        int i = 0;
        while (i < m * n)
        {
            numsnew[i / c][i % c] = nums[i / n][i % n];
            i++;
        }
        return numsnew;
    }
};
//遍历次数 1
class Solution
{
public:
    vector<int> spiralOrder(vector<vector<int>> &matrix)
    {

        int rl = 0, rr = matrix.size();
        int cl = 0, cr = matrix[0].size();
        int m = rr, n = cr;
        int i = 0;
        vector<int> result;
        while (i < m * n)
        {
            for (int k = cl; k < cr; k++)
            {
                result.push_back(matrix[rl][k]);
                i++;
            }
            rl++;
            for (int k = rl; (k <=rr - 1); k++)
            {
                result.push_back(matrix[k][cr - 1]);
                i++;
            }
            cr--;
            for (int k = cr-1; k >= cl&&rl<rr; k--)
            {
                result.push_back(matrix[rr - 1][k]);
                i++;
            }
            rr--;
            for (int k = rr - 1; k >=rl&&cl<cr; k--)
            {
                result.push_back(matrix[k][cl]);
                i++;
            }
            cl++;
        }
        return result;
    }
};

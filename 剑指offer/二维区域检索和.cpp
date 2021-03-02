class NumMatrix
{
    vector<vector<int>> presums;
public:
    NumMatrix(vector<vector<int>> &matrix)
    {
        int m = matrix.size();
        if (m)
        {
            int n = matrix[0].size();
            vector<int> line;
            line.resize(n);
            for (int i = 0; i < m; i++)
                presums.push_back(line);
            for (int i = 0; i < m; i++)
                for (int j = 0; j < n; j++)
                {

                    presums[i][j] = (i - 1 < 0 ? 0 : presums[i - 1][j]) + (j - 1 < 0 ? 0 : presums[i][j - 1]) - ((i - 1 < 0 || j - 1 < 0) ? 0 : presums[i - 1][j - 1]) + matrix[i][j];
                }
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2)
    {
        int s1 = presums[row2][col2];
        int s2 = col1 - 1 < 0 ? 0 : presums[row2][col1 - 1];
        int s3 = row1 - 1 < 0 ? 0 : presums[row1 - 1][col2];
        int s4 = (row1 - 1 < 0 || col1 - 1 < 0) ? 0 : presums[row1 - 1][col1 - 1];
        return s1 - s2 - s3 + s4;
    }
};

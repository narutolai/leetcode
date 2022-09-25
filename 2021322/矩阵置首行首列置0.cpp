//给定一个矩阵 如果存在0，则把其首行首列的值全都变成0，重点在于要使用常数的存储空间。

class Solution
{
public:
    void setZeroes(vector<vector<int>> &matrix)
    {
        bool row0HasZero = false;
        bool col0HasZero = false;
        for (int i = 0; i < matrix.size(); i++)
            for (int j = 0; j < matrix[0].size(); j++)
            {
                if (matrix[i][j] == 0)
                {
                    if (i == 0)
                        row0HasZero = true;
                    if (j == 0)
                        col0HasZero = true;
                    matrix[i][0] = 0; //该行该列的第一个元素记录改行该列是否存在0
                    matrix[0][j] = 0;
                }
            }
        //然后从第二行和第二列开始改变值
        for (int i = 1; i < matrix.size(); i++)
        {
            for (int j = 1; j < matrix[i].size(); j++)
                if (matrix[0][j] == 0 || matrix[i][0] == 0)
                    matrix[i][j] = 0;
        }

        //最后要记得修改第一行和第一列
        if (row0HasZero)
            for (int i = 0; i < matrix[0].size(); i++)
                matrix[0][i] = 0;
        if (col0HasZero)
            for (int i = 0; i < matrix.size(); i++)
                matrix[i][0] = 0;
    }
};
//遍历次数 
//卧槽没懂????
//卧槽没懂????
//卧槽没懂????
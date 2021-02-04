将一个给定字符串 s 根据给定的行数 numRows ，以从上往下、从左到右进行 Z 字形排列。

比如输入字符串为 "PAYPALISHIRING" 行数为 3 时，排列如下：

P   A   H   N
A P L S I I G
Y   I   R
之后，你的输出需要从左往右逐行读取，产生出一个新的字符串，比如："PAHNAPLSIIGYIR"。

请你实现这个将字符串进行指定行数变换的函数：

string convert(string s, int numRows);
 

示例 1：

输入：s = "PAYPALISHIRING", numRows = 3
输出："PAHNAPLSIIGYIR"
示例 2：
输入：s = "PAYPALISHIRING", numRows = 4
输出："PINALSIGYAHRPI"
解释：
P     I    N
A   L S  I G
Y A   H R
P     I
示例 3：

输入：s = "A", numRows = 1
输出："A"
 
提示：
1 <= s.length <= 1000
s 由英文字母（小写和大写）、',' 和 '.' 组成
1 <= numRows <= 1000
class Solution {
public:
    string convert(string s, int numRows) {

      //假设有一个方格
    int count = 0, x = 0, y = 0;

    //先设置一个往下走的标志为true
    bool down = true;
    //先准备一个numRow*500的矩阵
    vector<vector<char>> matrix(numRows,vector<char>(500));
    //遍历字符串
    while (count != (int)s.size())
    {
        if (x < 0)
        {
            x = 0;
        }
        //先往下 所以判断其为0
        if (x == 0)
        {
            down = true;
        }
        //再判断其到底
         if (x == numRows - 1 || x == numRows)
        {
            down = false;
        }
        
        matrix[x][y] = s[count];
        count++;
        if (down)
        {
            x++;
        }
        else
        {
            x--;
            y++;
        }
    }

    string result;
    //我觉得主要是这个后面的遍历矩阵花时间太长了
    for (int i = 0; i < (int)matrix.size(); i++)
        {
            for (int j = 0; j < (int)matrix[0].size(); j++)
                if(matrix[i][j]!='\000')
                result+=matrix[i][j];
        }
    return result;
    }
};

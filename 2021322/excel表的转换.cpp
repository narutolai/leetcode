// 1 -> A
// 2 -> B
// 3 -> C
// ...
// 26 -> Z
// 27 -> AA
// 28 -> AB 

class Solution
{
public:
    string convertToTitle(int columnNumber)
    {
        string result;
        int mod = 0;
        while (columnNumber)
        {
            mod = columnNumber % 26;
            //因为这个26进制没有0 ，所以当我们取得余数为0的时候，单独拆一个26出来 
            if (mod == 0)
            {
                columnNumber -= 26;
                result.push_back('Z');
            }
            else
            {
                result.push_back(char(mod + 64));
            }
            columnNumber /= 26;
        }
        reverse(result.begin(), result.end());
        return result;
    } 
};

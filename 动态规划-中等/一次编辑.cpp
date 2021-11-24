// 字符串有三种编辑操作:插入一个字符、删除一个字符或者替换一个字符。
// 给定两个字符串，编写一个函数判定它们是否只需要一次(或者零次)编辑。
// 示例 1:

// 输入:
// first = "pale"
// second = "ple"
// 输出: True
//  

// 示例 2:

// 输入:
// first = "pales"
// second = "pal"
// 输出: False

class Solution
{
public: //aabb abcd;
    bool oneEditAway(string first, string second)
    {
        int len = first.size() - second.size();
        if (len > 1 || len < -1)
            return false; //长度差大于1直接返回false
        int count = 1;
        for (int i = 0, j = 0; i < first.size() && j < second.size(); i++, j++)
        {
            if (first[i] != second[j])
            {
                if (len == 1)
                    j--; //长度短的停留一次不要
                else if (len == -1)
                    i--; //删除

                count--; //如果不等的话 肯定要一次操作的
            }
            if (count < 0)
                return false;
        }
        return true;
    }
};

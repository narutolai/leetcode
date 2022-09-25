// s=""
// s="            "
// s=",,,    ,,,, hello world ,,,"
class Solution
{
public:
    bool isAlpha(char c)
    {
        return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
    }
    int countSegments(string s)
    {
        int iWordCount = 0;
        for (int i = 0; i < s.size(); i++)
        {
            if (isAlpha(s[i]))
            {
                iWordCount++;
                while (isAlpha(s[i]) && i < s.size())
                {
                    i++;
                }
            }
        }
        return iWordCount;
    }
};
//不觉得第二种方法好多了吗
//遍历次数 2 确实第2种更好
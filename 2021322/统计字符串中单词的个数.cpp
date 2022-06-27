// s=""
// s="            "
// s=",,,    ,,,, hello world ,,,"

class Solution
{
public:
    int countSegments(string s)
    {
        int count = 0;
        //去掉尾部空格
        while (!s.empty() && s.back() == ' ')
        {
            s.pop_back();
        }
        if (s.size() == 0)
            return 0; //空字符串

        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] != ' ')
            {
                for (int j = i; j < s.size();)
                {
                    if (s[j] == ' ')
                    {
                        count++;
                        while (s[j] == ' ')
                            j++;
                    }
                    else
                    {
                        j++;
                    }
                }
                break;
            }
        }
        return count + 1;
    }
};

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
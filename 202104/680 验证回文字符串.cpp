//给定一个字符串，你只可以删除一次一个字符，然后看它是不是回文串。
class Solution
{
public:
    bool validPalindrome(string s)
    {
        int i = 0, j = s.size() - 1;
        int time = 1;
        while (i <= j)
        {
            if (s[i] == s[j])
            {
                i++;
                j--;
            }
            else
            {
                j--;
                if (time == 0)
                    break;
                time--;
            }
        }
        if (i > j)
            return true;

            
        i = 0;
        j = s.size() - 1;
        time = 1;
        while (i <= j)
        {
            if (s[i] == s[j])
            {
                i++;
                j--;
            }
            else
            {
                i++;
                if (time == 0)
                    break;
                time--;
            }
        }
        if (i > j)
            return true;
        return false;
    }
};

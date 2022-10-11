//找到字符串中的所有字母异位词
//给一个字符串s 和字符串p  找到s中所有是p的字母异位词的字串 返回这些字串的起始位置
//s="cbadefbac"   p="abc"
// res=[0,6] 就是 cba  里有abc   bac里也有abc
class Solution
{
public:
    vector<int> Exist(string s, string t)
    {

        map<char, int> need;
        for (auto c : t)
            need[c]++;
        map<char, int> window;

        vector<int> res;
        int left = 0;
        int right = 0;
        int match = 0;

        while (right <= s.size())
        {
            char c = s[right];
            //如果字符需要统计
            if (need[c])
            {
                window[c]++;
                if (window[c] == need[c])
                    match++; //match数
            }
            right++;
            while (match == need.size())
            {
                if (right - left == t.size())//数量符合长度一样 
                {
                    res.push_back(left);
                }
                char c = s[left];
                if (need[c])
                {
                    window[c]--;
                    if (window[c] < need[c])
                        match--;
                }

                left++;
            }
        }
        return res;
    }
};
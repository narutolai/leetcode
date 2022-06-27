
//最小覆盖字串
//给你一个字符串S 和字符串T 请在S里找出包含T所有字母的最小字串
// S="ADDDBFGTRFBANC" T ="ABC"

class Solution
{
public:
    string Exist(string s, string t)
    {
        map<char, int> need;
        for (auto c : t)
            need[c]++;
        map<char, int> window;
        int left = 0;
        int right = 0;
        int match = 0;
        int minLen = INT_MAX;
        int start = 0;
        while (right <= s.size())
        {
            char c = s[right];
            //如果字符需要统计
            if (need[c])
            {
                window[c]++;
                if (window[c] == need[c])
                    match++; //统计符合条件
            }
            right++;
            while (match == need.size())
            {
                if (right - left < minLen)
                {
                    start = left;
                    minLen = right - left;
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
        return minLen == INT_MAX ? "" : s.substr(start, minLen);
    }
};

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
                if (right - left == t.size())
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
//无重复字符的最长字串
//给定一个字符串 请你找出其中不含有重复字符的最长字串的长度
//s ="abcabcbb"  长度为3
//s="bbbbbb"  长度为1
//s="pwwkew"  长度为3
class Solution
{
public:
    string Exist(string s, )
    {
        map<char, int> window;
        int res = 0;
        int left = 0;
        int right = 0;
        while (right <= s.size())
        {
            char c = s[right];
            window[c]++;
            right++;
            while (window[c] > 1)
            {
                char c = s[left];
                window[c]--;
                left++;
            }
            res = max(res, right - left);
        }
        return res;
    }
};
//遍历次数 1
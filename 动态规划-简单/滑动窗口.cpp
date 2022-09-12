
//最小覆盖字串
//给你一个字符串S 和字符串T 请在S里找出包含T所有字母的最小字串
// S="ADDDBFGTRFBANC" T ="ABC"

class Solution
{
public:
    string Exist(string s, string t)//两个窗口,一个是need window 还有一个是 window
    {
        map<char, int> need;
        for (auto c : t)
            need[c]++;
        map<char, int> window;
        int left = 0;
        int right = 0;
        int match = 0;//匹配数是关键 
        int minLen = INT_MAX;
        int start = 0;
        while (right <= s.size())
        {
            char c = s[right];
            //如果字符需要统计 如果字符是需要统计的字符的话
            if (need[c])
            {
                window[c]++;//如果需要统计才计入窗口中,如果需要统计才计入窗口中。
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
//window和need window和need ，window和need。window和need window和need window和need  window和need
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
//第2题和第1题是一样的啊
//无重复字符的最长字串
//给定一个字符串 请你找出其中不含有重复字符的最长字串的长度
//s ="abcabcbb"  长度为3
//s="bbbbbb"  长度为1
//s="pwwkew"  长度为3
class Solution
{
public:
    int Exist(string &s)
    {
        map<char, int> window;
        int res = 0;
        int left = 0;
        int right = 0;
        while (right <= s.size())
        {
            char c1 = s[right];
            window[c1]++;
            right++;
            //当窗口中出现重复的子串时,左边缩小 直到这个字符的出现次数不大于1
            while (window[c1] > 1)
            {
                char c2 = s[left];
                window[c2]--;
                left++;
            }
            //每次往右边移动一次都会求一次max
            res = max(res, right - left);
        }
        return res;
    }
};
//遍历次数 第3次 2022-09-07 17:36
//两个while循环
//还行吧 算是又加深一遍记忆了
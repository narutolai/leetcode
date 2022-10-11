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
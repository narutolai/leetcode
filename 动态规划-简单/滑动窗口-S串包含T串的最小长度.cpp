
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

//第2题和第1题是一样的啊

//遍历次数 第3次 2022-09-07 17:36
//两个while循环
//还行吧 算是又加深一遍记忆了
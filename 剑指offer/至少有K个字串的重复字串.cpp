// 395 中等  递归与分治
// 给你一个字符串 s 和一个整数 k ，请你找出 s 中的最长子串， 要求该子串中的每一字符出现次数都不少于 k 。返回这一子串的长度。

//  

// 示例 1：

// 输入：s = "aaabb", k = 3
// 输出：3
// 解释：最长子串为 "aaa" ，其中 'a' 重复了 3 次。
// 示例 2：

// 输入：s = "ababbc", k = 2
// 输出：5
// 解释：最长子串为 "ababb" ，其中 'a' 重复了 2 次， 'b' 重复了 3 次。

class Solution
{
public:
    int longestSubstring(string s, int k)
    {
        map<char, int> count;
        //统计s中每一个字符出现的次数
        for (auto &c : s)
            count[c]++;

        //找出切分点
        vector<int> index;
        index.push_back(-1);
        
        for (int i = 0; i < s.size(); i++)
            if (count[s[i]] < k)
            {
                index.push_back(i);
            }
        //如果没有切分 那就返回整个串的长度
        if (index.size() == 1)
            return s.size();

        index.push_back(s.size());
        //否则就要遍历切分成的段 然后再比较每一个段能有的最大长度
        int res = 0;
        for (int i = 0; i < index.size() - 1; i++)
        {
            int len = index[i + 1] - index[i] - 1;
            if (len >= k && len > res)
            {
                res = max(res, longestSubstring(s.substr(index[i] + 1, len), k));
            }
        }
        return res;
    }
};

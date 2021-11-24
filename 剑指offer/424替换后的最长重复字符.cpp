// 给你一个仅由大写英文字母组成的字符串，你可以将任意位置上的字符替换成另外的字符，总共可最多替换 k 次。在执行上述操作后，
//  找到包含重复字母的最长子串的长度。

//     注意：字符串长度 和 k 不会超过 104。

//  

//     示例 1：

//     输入：s = "ABAB",
//     k = 2 输出：4
//         解释：用两个 'A'替换为两个 'B',
//     反之亦然。 示例 2：

//     输入：s = "AABABBA",
//     k = 1 输出：4
//         解释：
//             将中间的一个 'A'替换为 'B',
//     字符串变为 "AABBBBA"。 子串 "BBBB" 有最长重复字母, 答案为 4。

class Solution
{
public:
    //写一个函数判断最长重复子串

    int characterReplacement(string s, int k)
    {
        if (s.size() == 0)
            return 0;
        map<char, int> count;
        int maxcount = 0;

        int left = 0;
        for (int i = 0; i < s.size(); i++)
        {
            //当前窗口内各个字符的出现次数
            count[s[i]]++;
            //当前窗口内最大出现次数
            maxcount = max(maxcount, count[s[i]]);
            //如果最大出现次数加上
            if (i - left + 1 > maxcount + k)
            {
                count[s[left]]--;
                left++;
            }
        }
        return s.size() - left;
    }
};

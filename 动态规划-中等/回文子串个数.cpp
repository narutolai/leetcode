// 给定一个字符串，你的任务是计算这个字符串中有多少个回文子串。

// 具有不同开始位置或结束位置的子串，即使是由相同的字符组成，也会被计为是不同的子串。

// 示例 1:

// 输入: "abc"
// 输出: 3
// 解释: 三个回文子串: "a", "b", "c".
// 示例 2:

// 输入: "aaa"
// 输出: 6
// 说明: 6个回文子串: "a", "a", "a", "aa", "aa", "aaa".

/**
 * a      1
 *  a     2
 * aa
 *   a    3
 *  aa
 * aaa
*/
class Solution
{
public:
    int countSubstrings(string s)
    {
        int len = s.size();
        vector<int> dp(len);
        int cnt = 0;
        for (int i = 0; i < len; i++)
        {
            dp[i] = 1;
            cnt++;
            for (int j = 0; j < i; j++)
            {
                if (s[j] == s[i] && dp[j + 1] == 1)
                {
                    dp[j] = 1;
                    cnt++;
                }
                else
                    dp[j] = 0;
            }
        }
        return cnt;
    }
};
//每次出现一个数都会把之前的都更新的
//dp[i] = 1表示 dp[i]可以与后面的数构成回文串
//一维dp数组
//如果是 a b c b c a
//那么就是慢慢开始
/**
 * a
 * a b
 * a b c
 * a b c b
 * a b c b c
 * a b c c c a
*/
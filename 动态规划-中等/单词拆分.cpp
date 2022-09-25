// 给定一个非空字符串 s 和一个包含非空单词列表的字典 wordDict，判定 s 是否可以被空格拆分为一个或多个在字典中出现的单词。

// 说明：

// 拆分时可以重复使用字典中的单词。
// 你可以假设字典中没有重复的单词。
// 示例 1：

// 输入: s = "leetcode", wordDict = ["leet", "code"]
// 输出: true

// 解释: 返回 true 因为 "leetcode" 可以被拆分成 "leet code"。
// 示例 2：
// 输入: s = "applepenapple", wordDict = ["apple", "pen"]
// 输出: true
// 解释: 返回 true 因为 "applepenapple" 可以被拆分成 "apple pen apple"。
//      注意你可以重复使用字典中的单词。
// 示例 3：
// 输入: s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"]
// 输出: false

// dp[i]表示字符串s的前i个字符能否拆分成wordDict

class Solution
{
public:
    bool wordBreak(string s, vector<string> &wordDict)
    {
        //这个使用dp吗
        vector<bool> dp(s.size() + 1, false);
        //这种方式初始化吗
        unordered_set<string> m(wordDict.begin(), wordDict.end());

        dp[0] = true;
        for (int i = 1; i <= s.size(); i++)
            for (int j = 0; j < i; j++)
            { //i-j的字符串找到了
                if (dp[j] && m.find(s.substr(j, i - j)) != m.end())
                {
                    dp[i] = true; //只要有true,就到下一个i
                    break;
                }
            }
        return dp[s.size()];
    }
};
//dp[i] =dp[j] && find(i-j) 这里也是有一个动态规划吗
//时间复杂度On方 
//不知道有没有时间复杂度更低的方法
//我怎么想成了0,1背包问题呢
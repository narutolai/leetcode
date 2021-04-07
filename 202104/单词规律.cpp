给定一种规律 pattern 和一个字符串 str ，判断 str 是否遵循相同的规律。

这里的 遵循 指完全匹配，例如， pattern 里的每个字母和字符串 str 中的每个非空单词之间存在着双向连接的对应规律。

示例1:

输入: pattern = "abba", str = "dog cat cat dog"
输出: true
示例 2:

输入:pattern = "abba", str = "dog cat cat fish"
输出: false
示例 3:

输入: pattern = "aaaa", str = "dog cat cat dog"
输出: false
示例 4:

输入: pattern = "abba", str = "dog dog dog dog"
输出: false

class Solution
{
public:
    bool wordPattern(string pattern, string s)
    {
        //创建两个映射
        map<char, string> c2s;
        map<string, char> s2c;

        //切分单词
        vector<string> words;
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] != ' ')
            {
                string word;
                while (s[i] != ' ' && i < s.size())
                {
                    word += s[i];
                    i++;
                }
                words.push_back(word);
            }
        }
        //数量不一样直接返回
        if(words.size()!=pattern.size()) return false;
      //检验两个方向的映射
        for (int i = 0; i < pattern.size(); i++)
        {
            if (c2s[pattern[i]] == "")
            {
                c2s[pattern[i]] = words[i];
            }
            else
            {
                if (c2s[pattern[i]] != words[i])
                    return false;
            }
        }

         for (int i = 0; i < words.size(); i++)
        {
            if (s2c[words[i]])
            {
                 if (s2c[words[i]] != pattern[i])
                    return false;
            }
            else
            {
                s2c[words[i]] = pattern[i];
            }
        }
        return true;
    }
};
确实很慢啊

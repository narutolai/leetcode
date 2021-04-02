给你一个字符串 sequence ，如果字符串 word 连续重复 k 次形成的字符串是 sequence 的一个子字符串，那么单词 word 的 重复值为 k 。单词 word 的 最大重复值 是单词 word 在 sequence 中最大的重复值。如果 word 不是 sequence 的子串，那么重复值 k 为 0 。

给你一个字符串 sequence 和 word ，请你返回 最大重复值 k 。

 

示例 1：

输入：sequence = "ababc", word = "ab"
输出：2
解释："abab" 是 "ababc" 的子字符串。



class Solution
{
public:
    int maxRepeating(string sequence, string word)
    {
        int m = sequence.size();
        int n = word.size();
        int result = 0;
        int st = 0;
        int i=0,j=0,k=0;
        while (i < m)
        {
            if (sequence[i] == word[0])
            {
                j = 0;
                st = i;
                k=i;
                while (k < m && sequence[k] == word[j])//这个取余方式很关键
                {
                    j++;
                    k++;
                    j %= n;
                }
                result = max(result, (k - st) / n);
            }
           i++;
        }
        return result;
    }
};

// 给你一个字符串 sequence ，如果字符串 word 连续重复 k 次形成的字符串是 sequence 的一个子字符串，那么单词 word 的 重复值为 k 。
// 单词 word 的 最大重复值 是单词 word 在 sequence 中最大的重复值。如果 word 不是 sequence 的子串，那么重复值 k 为 0 。

// 给你一个字符串 sequence 和 word ，请你返回 最大重复值 k 。

// 示例 1：
// 输入：sequence = "ababc", word = "ab"
// 输出：2
// 解释："abab" 是 "ababc" 的子字符串。
class Solution
{
public:
    int maxRepeating(string sequence, string word)
    {
        int sSize = sequence.size();
        int wSize = word.size();
        int index = 0;
        int result = 0;
        while (index < sSize)
        {
            if (sequence[index] == word[0])
            {
                int curSor = index;
                int wIndex = 0;
                while (curSor < sSize && word[wIndex] == sequence[curSor])
                {
                    wIndex++;
                    curSor++;
                    wIndex %= wSize;
                }
                result = max(result, (curSor - index) / wSize);
            }
            //
            index++;
        }
        return result;
    }
};
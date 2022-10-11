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
                    wIndex %= wSize;//对其取余
                }
                //优化还是可以优化的.....
                result = max(result, (curSor - index) / wSize);//最大重复次数
            }
            //
            index++;
        }
        return result;
    }
};
//注意这个要连续重复多少次才行
//2022/10/03
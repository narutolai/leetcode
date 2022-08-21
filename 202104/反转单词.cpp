// 输入一个英文句子，翻转句子中单词的顺序，但单词内字符的顺序不变。为简单起见，标点符号和普通字母一样处理。
// 例如输入字符串"I am a student. "，则输出"student. a am I"。

//  

// 示例 1：

// 输入: "the sky is blue"
// 输出: "blue is sky the"
// 示例 2：

// 输入: "  hello world!  "
// 输出: "world! hello"
// 解释: 输入字符串可以在前面或者后面包含多余的空格，但是反转后的字符不能包括。

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/fan-zhuan-dan-ci-shun-xu-lcof
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

//大体是这么做 if里边 再加一个while循环就行了。
class Solution
{
public:
    string reverseWords(string s)
    {
        string result;
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] != ' ')
            {
                string word;
                while (s[i] != ' ' && i < s.size()) //可以直接截取substr吧
                {
                    word += s[i];
                    i++;
                }
                result.insert(0, " " + word);
            }
        }

        result.erase(0, 1);
        return result;
    }

    string reverseWords(string st1)
    {
        string result;
        for (int i = 0; i < st1.size(); i++)
        {
            if (st1[i] != ' ')
            {
                string word;
                int stindex = i;
                while (st1[i] != ' ' && i < st1.size()) //这里换成直接记录起始坐标。
                {
                    i++;
                }
                result.insert(0, " " + st1.substr(stindex, i - stindex));
            }
        }
        result.erase(0, 1);
    }
};

//遍历次数: 2
//还算有意思吧
//这是原题描述
// https : //leetcode-cn.com/problems/letter-combinations-of-a-phone-number/

class Solution
{
public:
    vector<string> letterCombinations(string digits)
    {
        map<char, vector<string>> map_;
        vector<string> result;
        map_['2'] = {"a", "b", "c"};
        map_['3'] = {"d", "e", "f"};
        map_['4'] = {"g", "h", "i"};
        map_['5'] = {"j", "k", "l"};
        map_['6'] = {"m", "n", "o"};
        map_['7'] = {"p", "q", "r", "s"};
        map_['8'] = {"t", "u", "v"};
        map_['9'] = {"w", "x", "y", "z"};

        for (int i = 0; i < digits.size(); i++)
        {
            //存储临时结果
            vector<string> result_temp;
            //取出当前数字的字母合集
            vector<string> cur = map_[digits[i]];
            //然后遍历当前数字的字母
            for (auto ch : cur)
            {
                if (result.size() > 0)
                    //将当前字母和上一次的result的结果合并 就是当前结果的
                    for (auto item : result)
                    {
                        string s = item + ch;
                        result_temp.push_back(s);
                    }
                else
                {
                    string s = ch;
                    result_temp.push_back(s);
                }
            }
            //这里把临时结果赋给result
            result = result_temp;
        }
        return result;
    }
};
//这个可以直接递归呀
class Solution
{
public:
    vector<string> result;
    vector<string> letterCombinations(string digits)
    {
        map<char, vector<string>> map_;
        map_['2'] = {"a", "b", "c"};
        map_['3'] = {"d", "e", "f"};
        map_['4'] = {"g", "h", "i"};
        map_['5'] = {"j", "k", "l"};
        map_['6'] = {"m", "n", "o"};
        map_['7'] = {"p", "q", "r", "s"};
        map_['8'] = {"t", "u", "v"};
        map_['9'] = {"w", "x", "y", "z"};
        string str;
        backtrace(digits, map_, 0, str);
    }
    void backtrace(string &digits, map<char, vector<string>> &map_, int index, string &str)
    {
        if (index == digits.size())
        {
            result.push_back(str);
            return;
        }
        vector<string> &num2alpha = map_[digits[index]];
        for (auto ch : num2alpha)
        {
            str += ch;
            backtrace(digits, map_, index + 1, str);
            str.pop_back();
        }
    }
};
//2022/09/.25 把这道题直接换成递归来解答,一般能画出n叉树的都是可以直接递归的.
// 请实现一个函数，把字符串 s 中的每个空格替换成"%20"。

//  

// 示例 1：

// 输入：s = "We are happy."
// 输出："We%20are%20happy."
//  

// 限制：

// 0 <= s 的长度 <= 10000

// 通过次数34,930提交次数45,533

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/ti-huan-kong-ge-lcof
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

//只要再重新累加一遍就可以了
class Solution
{
public:
    string replaceSpace(string s)
    {
        string ans;
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == ' ')
                ans += "%20";
            else
                ans += s[i];
        }
        return ans;
    }
};

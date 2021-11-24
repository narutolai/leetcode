// 给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串 s ，判断字符串是否有效。

// 有效字符串需满足：

// 左括号必须用相同类型的右括号闭合。
// 左括号必须以正确的顺序闭合。
//  

// 示例 1：

// 输入：s = "()"
// 输出：true
// 示例 2：

// 输入：s = "()[]{}"
// 输出：true
// 示例 3：

// 输入：s = "(]"
// 输出：false
// 示例 4：

// 输入：s = "([)]"
// 输出：false
class Solution
{
public:
    char leftof(char c)
    {
        if (c == '(')
            return ')';
        else if (c == '[')
            return ']';
        else if (c == '{')
            return '}';
    }
    bool isValid(string s)
    {

        stack<char> st;
        for (auto &cha : s)
        {
            switch (cha)
            {
            case ')':
                if (!st.empty() && st.top() == '(')
                {
                    st.pop();
                }
                else
                {
                    st.push(cha);
                }
                break;
            case ']':
                if (!st.empty() && st.top() == '[')
                {
                    st.pop();
                }
                else
                {
                    st.push(cha);
                }
                break;
            case '}':
                if (!st.empty() && st.top() == '{')
                {
                    st.pop();
                }
                else
                {
                    st.push(cha);
                }
                break;
            default:
                st.push(cha); //default中处理当前字符是左括号类型的话直接入栈。
                break;
            }
        }
        return st.empty();
    }
};

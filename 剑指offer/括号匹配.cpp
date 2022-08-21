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
        if (c == ')')
            return '(';
        else if (c == ']')
            return '[';
        else if (c == '}')
            return '{';
    }
    bool isValid(string s)
    {

        stack<char> st;
        for (auto &cha : s)
        {
           if (cha == ')' || cha == '}' || cha== ']')
            {
                if(!st.empty() && st.top() == leftof(cha))
                {
                    st.pop();
                }else{
                    st.push(cha);// 这里是不是可以直接返回false了
                    //return false; //可以直接返回false了
                }
            }
            else{
                st.push(cha);
            }
        }
        return st.empty();
    }
};
//遍历次数 1,左括号入栈，遇见右括号看能否弹出 最后返回栈是否是空的
// 可以直接返回false
// 根据 逆波兰表示法，求表达式的值。

// 有效的算符包括 +、-、*、/ 。每个运算对象可以是整数，也可以是另一个逆波兰表达式。

//  

// 说明：

// 整数除法只保留整数部分。
// 给定逆波兰表达式总是有效的。换句话说，表达式总会得出有效数值且不存在除数为 0 的情况。
//  

// 示例 1：

// 输入：tokens = ["2","1","+","3","*"]
// 输出：9
// 解释：该算式转化为常见的中缀算术表达式为：((2 + 1) * 3) = 9

class Solution
{
public:
    int evalRPN(vector<string> &tokens)
    {
        stack<int> st;
        for (auto &it : tokens)
        {
            //是通过最后一个字符来判断是不是数字
            if (it.back() >= '0' && it.back() <= '9')
            {
                st.push(atoi(it.c_str()));//字符串转整形。
            }
            else
            {
                int m = st.top();
                st.pop();
                int n = st.top();
                st.pop();
                switch (*it.c_str()) //这里返回的是一个指针，指向字符，所以只能取内容了 应该也可用char ch = it.c_str();
                {
                case '+':
                {
                    st.push(m + n);
                }
                break;
                case '-':
                {
                    st.push(n - m);
                }
                break;
                case '*':
                {
                    st.push(m * n);
                }
                break;
                case '/':
                {
                    st.push(n / m);//底下那个数/上面那个数比较好。
                }
                break;
                default:
                    break;
                }
            }
        }
        return st.top();
    }
};
//牛 牛 牛
//遍历次数 1
//可以的 这道题还是可以的
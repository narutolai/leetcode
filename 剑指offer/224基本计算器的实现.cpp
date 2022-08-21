//没有乘除法的办法 主要是括号的结局 这么写总是会超时 这样写就不会超时了
class Solution
{
public:
	int index = 0;
	bool isdigit(const char c)
	{
		return c >= '0' && c <= '9';
	}
	int calculate(string &s)
	{
		stack<int> stk;
		int num = 0;
		char sign = '+';
		char c;
		while (index < s.size())
		{
			c = s[index++];
			//s.erase(0,1);//是不是这里太费劲了
			if (isdigit(c))
			{ 	
				num = num * 10 + (c - '0');
			}
			
			if (c == '(')
			{
				num = calculate(s);
			}
			//是符号 或者 最后一个元素
			//if(c =='+'|| c=='-' || c=='*' || c=='\'|| index == s.size()) 这样是不是更快 就不用再调用isdigit()函数了。
			if (!isdigit(c) && c != ' ' || index == s.size()) //应该是erase()函数太费时间了
			{
				switch (sign)
				{
				case '+':
					stk.push(num);
					break;
				case '-':
					stk.push(-num);
					break;
				case '*':
					num = num * stk.top();
					stk.pop();
					stk.push(num);
					break;
				case '/':
					num = stk.top() / num;
					stk.pop();
					stk.push(num);
					break;
				default:
					break;
				}
				sign = c;
				num = 0;
			}
			
			if (c == ')')
				break;
		}//循环结束 累加栈中的元素值
		int result = 0;
		while (!stk.empty())
		{
			result += stk.top();
			stk.pop();
		}
		return result;
	}
};
//遍历次数+1
//注意栈中的元素最后会累加 4个纯if 没有else 然后累加栈中的元素
//index = s.size() 很难判断 当前符号是 = - * / 以及表达式的最后一个元素时要进入switch
//char c = s[index++] ;比较好
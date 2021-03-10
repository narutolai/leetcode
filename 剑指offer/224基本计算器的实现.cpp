//这是包含乘除法的 但是会超时 可能花在递归和s.earse()这个操作上，还有累加栈这个操作也费时间。。。原题是没有乘法和除法的。
//
bool isdigit(const char c)
{
	return c >= '0' && c <= '9';
}

//"2*(3+4)*2+1"
int calculate(string &s)
{
	stack<int> stk;
	int num = 0;
	char sign = '+';
	char c;
	while (!s.empty())
	{
		c = s.front();
		s.erase(0,1);
		if (isdigit(c))
		{
			num = num * 10 + (c - '0');
		}

		if (c == '(')
		{
			num = calculate(s);
		}
		//是符号 或者 最后一个元素
		if (!isdigit(c) && c != ' ' || s.size()==0)
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
	}
	int result = 0;
	while (!stk.empty())
	{
		result += stk.top();
		stk.pop();
	}
	return result;
}

//没有乘除法的办法 主要是括号的结局 这么写总是会超时 这样写就不会超时了
class Solution {
public:
    int index=0;
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
	while (index<s.size())
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
		if (!isdigit(c) && c != ' ' || index==s.size()) 应该是erase()函数太费时间了
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
	}
	int result = 0;
	while (!stk.empty())
	{
		result += stk.top();
		stk.pop();
	}
	return result;
}
};

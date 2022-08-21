#include <iostream>
#include <map>
using namespace std;
#include <string>
#include <stdio.h>
#include <cstring>
#include <vector>

#include <queue>
#include <string.h>

#include "stdio.h"

#include <iostream>
using namespace std;
class Solution
{
public:
    string traverse(int &index, string str)
    {
        string result;
        while (index < str.size())
        {
            char c = str[index];
            if (isalpha(c))
            {
                result += c;
            }
            else if (isdigit(c)) //如果碰见数字 要把数字累加
            {
                int n = 0;
                while (isdigit(c))
                {
                    n = n * 10 + atoi(&c);
                    index++;
                    c = str[index];
                }
                string temp = traverse(index, str);
                while (n--)
                    result += temp;
            }
            else if (c == ']')
            {
                return result;
            }
            index++;
        }
        return result;
    }
    string compress(string str)
    {
        int index = 0;
        return traverse(index, str);
    }
};
int main()
{
    Solution so; //遇见数字进入循环 遇见右中括号 退出循环
    string str = "AB[2|[1|EF]AD]";
    string result;
    result = so.compress(str);
    cout << result << endl;
    return 0;
}
//只过了8例子？？ 还有两个测试用例没有过
// 连续输入字符串，请按长度为8拆分每个字符串后输出到新的字符串数组；
// •长度不是8整数倍的字符串请在后面补数字0，空字符串不处理。
// 输入描述:
// 连续输入字符串(输入2次,每个字符串长度小于100)

// 输出描述:
// 输出到长度为8的新字符串数组

// 示例1
// 输入
// 复制
// abc
// 123456789
// 输出
// 复制
// abc00000
// 12345678
// 90000000

#include <iostream>
#include <vector>
#include <algorithm>
//#include <>
using namespace std;
int main()
{
    string str1;
    while (cin >> str1)
    {
        vector<string> result;
        //先把字符串凑成8的整数倍
        int mode = 8 - str1.size() % 8;
        while (mode)
        {
            str1 += '0';
            mode--;
        }
    
        string temp;
        //然后8个8个的截取就行了。
        for (int i = 0; i < str1.size(); i += 8)
        {
            temp = str1.substr(i, 8);
            result.push_back(temp);
        }
        for_each(result.begin(), result.end(), [](string &s) { cout << s << endl; });
    }
    return 0;
}

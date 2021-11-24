// 写出一个程序，接受一个由字母和数字组成的字符串，和一个字符，然后输出输入字符串中含有该字符的个数。不区分大小写。

// 输入描述:
// 第一行输入一个有字母和数字以及空格组成的字符串，第二行输入一个字符。

// 输出描述:
// 输出输入字符串中含有该字符的个数。

// 示例1
// 输入
// 复制
// ABCDEF
// A
// 输出
// 复制
// 1

// #这道题就是注意大小写卧槽
#include <iostream>
#include <unordered_map>
using namespace std;

int main()
{
    unordered_map<char, int> counts;

    string str1;
    char str2;
    cin >> str1 >> str2;

    for (int i = 0; i < str1.size(); i++)
    {
        counts[str1[i] | ' ']++;
    }
    cout << counts[(str2 | ' ')];
    return 0;
}

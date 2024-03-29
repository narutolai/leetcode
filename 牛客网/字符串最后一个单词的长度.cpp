// 计算字符串最后一个单词的长度，单词以空格隔开。
// 输入描述:
// 一行字符串，非空，长度小于5000。
// 输出描述:
// 整数N，最后一个单词的长度。

// 示例1
// 输入
// 复制
// hello world
// 输出
// 复制
// 5

#include <iostream>
#include <vector>
using namespace std;
int main()
{
    vector<string> s;
    string str;
    cin >> str;
    s.push_back(str);
    while (cin.get() != '\n')
    {
        cin >> str;
        s.push_back(str);
    }
    cout << s[s.size() - 1].size() << endl;
}

//牛客网读带空格的字符串 处理方式 cin.get()是只获取一个字符的 所以第一个字符不会读取的。    
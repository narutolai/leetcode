整形->字符  整形+48就行了
比如
int a=1;
char c=a+48; 如果不加上48,那么c就是ASCII码1号所对应的符号。
c='1'
字符->整形字符减去48得到的就是正确的结果。
char c='1';
int a=c-48; 如果不减去48 a就是字符‘1’所对应的ascii码的index。
a=1;

输入一个整数，将这个整数以字符串的形式逆序输出

程序不考虑负数的情况，若数字含有0，则逆序形式也含有0，如输入为100，则输出为001


输入描述:
输入一个int整数

输出描述:
将这个整数以字符串的形式逆序输出

示例1
输入
复制
1516000
输出
复制
0006151

#include<iostream>
#include<queue>
using namespace std;
int main()
{
    int x,c;
    queue<int> qu;
    cin>>x;
    while(x)
    {
        qu.push(x%10);
        x/=10;
    }
    string s;
    while(!qu.empty())
    {
        s+=qu.front()+48;
        qu.pop();
    }
    cout<<s<<endl;
    return 0;
}

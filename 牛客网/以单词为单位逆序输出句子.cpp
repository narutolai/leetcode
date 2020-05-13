#反转句子
将一个英文语句以单词为单位逆序排放。

输出描述:
得到逆序的句子

示例1
输入
复制
I am a boy
输出
复制
boy a am I


#include<iostream>
#include<stack>
#include<vector>
using namespace std;
int main()
{
    string s;
    stack<string> st;
    
    cin>>s;          //不写这个的话开头的输入就不会被计入进去 我也不知道为什么。
    st.push(s);
    while(cin.get()!='\n')  
    {
        cin>>s;
        st.push(s);
    }
    while(!st.empty())
    {
        cout<<st.top()<<" ";
        st.pop();
    }
    cout<<endl;
    return 0;
}

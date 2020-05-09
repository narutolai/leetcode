连续输入字符串，请按长度为8拆分每个字符串后输出到新的字符串数组；
•长度不是8整数倍的字符串请在后面补数字0，空字符串不处理。
输入描述:
连续输入字符串(输入2次,每个字符串长度小于100)

输出描述:
输出到长度为8的新字符串数组

示例1
输入
复制
abc
123456789
输出
复制
abc00000
12345678
90000000



#include<iostream>
#include<vector>
using namespace std;
int main()
{
    string str1;
    while(cin>>str1)
    {     vector<string> s;
        int size=str1.size();
        int num=size/8;     
        for(int i=0;i<num;i++)
        {
            string str2=str1.substr(0+i*8,8);//起始下标和长度
            s.push_back(str2);
        }
        int mod=size%8;                       //  0-7 8-15 16-23  24 25 26
        if(mod!=0)                  //如果余数为0那么就表明整除。
       { string str=str1.substr(size-mod,mod); // 27/8=3,27%8=3
        for(int i=mod;i<8;i++)
            str+='0';
        s.push_back(str);
        }           
        for(int i=0;i<s.size();i++)
            cout<<s[i]<<endl;    
    }
    return 0;
}

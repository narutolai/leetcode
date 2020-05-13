他是这么变换的，大家都知道手机上的字母： 1--1， abc--2, def--3, ghi--4, jkl--5, mno--6, pqrs--7, tuv--8 wxyz--9, 0--0,
就这么简单，渊子把密码中出现的小写字母都变成对应的数字，数字和其他的符号都不做变换，


声明：密码中没有空格，而密码中出现的大写字母则变成小写之后往后移一位，
如：X，先变成小写，再往后移一位，不就是y了嘛，简单吧。记住，z往后移是a哦。

//大佬的解题思路
#include<iostream>
#include<string>
using namespace std;
const string dict1="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
const string dict2="bcdefghijklmnopqrstuvwxyza22233344455566677778889999";
 
char Char_Change(char a){
    for(int i=0;i<dict1.size();i++)
        if(dict1[i]==a) return dict2[i];
    return a;
}
 
int main(){
    //string data="YUANzhi1987";
    string data;
    while(getline(cin,data)){
        for(int i=0;i<data.size();i++)
            data[i] = Char_Change(data[i]);
        cout<<data<<endl;
    }
    return 0;
}

我的思路
#include<iostream>
using namespace std;
int main()
{
    int a[10]={'0','1','abc','def','ghi','jkl','mno','pqrs','tuv','wxyz'};
    string s;
    while(cin>>s)
    { 
        for(int i=0;i<s.size();i++)
        {
            if(s[i]>='A'&&s[i]<='Z')
            {
                if(s[i]=='Z') s[i]='a';
                else {char c=1+s[i]|' ';
                     s[i]=c;
                     }
            }
            else if(s[i]>='a'&&s[i]<='c')//分段函数
            {
                s[i]='2';
            }
            else if(s[i]>='d'&&s[i]<='f')
            {
                s[i]='3';
            }
            else if(s[i]>='g'&&s[i]<='i')
            {
                s[i]='4';
            }
            else if(s[i]>='j'&&s[i]<='l')
            {
                s[i]='5';
            }
            else if(s[i]>='m'&&s[i]<='o')
            {
                s[i]='6';
            }
            else if(s[i]>='p'&&s[i]<='s')
            {
                s[i]='7';
            }
            else if(s[i]>='t'&&s[i]<='v')
            {
                s[i]='8';
            }
            else if(s[i]>='w'&&s[i]<='z')
            {
                s[i]='9';
            }
            else continue;
        }
        cout<<s<<endl;
    }
    return 0;
}

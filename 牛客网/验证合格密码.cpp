密码要求:

1.长度超过8位

2.包括大小写字母.数字.其它符号,以上四种至少三种

3.不能有相同长度超2的子串重复


说明:长度超过2的子串

输入描述:
一组或多组长度超过2的子符串。每组占一行

输出描述:
如果符合要求输出：OK，否则输出NG

示例1
输入
复制
021Abc9000
021Abc9Abc1
021ABC9000
021$bc9000
输出
复制
OK
NG
NG
OK



#include<iostream>
#include<numeric>
using namespace std;

int main()
{ 
      string s;  
      while(cin>>s){ 
        int flag[4]={0,};
        int c=0;
        if(s.size()<=8) {cout<<"NG"<<endl;continue;}
         for(int i=0;i<s.size();i++)
        {   
            //cout<<"now is word"<<s[i]<<endl;
            string temp=s.substr(i,3); //从i位置处截取3个字符
            if(s.size()>=4)           //至少要长度大于等于4才有重复出现 比如 aaaa 不符合
            if(s.find(temp,i+1)!=s.npos){c=1;break;}

            if(s[i]>='0'&&s[i]<='9')     flag[0]=1;
            else if(s[i]>='a'&&s[i]<='z')flag[1]=1;
            else if(s[i]>='A'&&s[i]<='Z')flag[2]=1;
            else flag[3]=1;
        }
        int sum=0;
        for(int i=0;i<4;i++)  
            sum+=flag[i];
        if(sum<3)c=1;

       if(c==1) cout<<"NG"<<endl;
          else cout<<"OK"<<endl;
}
        return 0;
}

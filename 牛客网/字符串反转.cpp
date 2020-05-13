输入abcd
输出dcba

#include<iostream>
#include<stack>
using namespace std;
int main()
{
   string s;
   cin>>s;
   string s1;
   for(int i=s.size()-1;i>=0;i--)
        s1+=s[i];
  cout<<s1<<endl;

  return 0;
}

#include<iostream>
using namespace std;
int main()
{
    string  s;
    while(cin>>s)
    {
       int a[26]={0,};
       for(int i=0;i<s.size();i++)
           a[s[i]-'a']++;
        
        int min=a[s[0]-'a'];
        for(int i=1;i<s.size();i++)
            if(a[s[i]-'a']<min)
                min=a[s[i]-'a'];
        
        for(int i=0;i<s.size();i++)
            if(a[s[i]-'a']>min)
                cout<<s[i];
        cout<<endl;
    }
    return 0;
}

#include<iostream>
#include<unordered_map>
using namespace std;
int main()
{
    //分不分大小写啊？？
    int a[26];
    unordered_map<char,int> counts;
    string s;
    cin>>s;
    for(int i=0;i<s.size();i++)
        counts[s[i]]=1;
    
    unordered_map<char,int>::iterator iter;
    int sum=0;
    for(iter=counts.begin();iter!=counts.end();iter++)
        sum+=iter->second;
    cout<<sum<<endl;
    return 0;
}

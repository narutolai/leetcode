
就是一个数组去重 但是这牛客网也太奇怪了吧 这种符合要求的输入方式。
还有这个算法包 algorithm
#include<iostream>
#include<algorithm>
using namespace std;
int main()
{
    int n;
    while(cin>>n)
    {  
    int a[n];
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
    }
    int j=0;// 1 2 2 2 3 3 
        sort(a,a+n);
    for(int i=1;i<n;i++)
    {
        if(a[i]!=a[j])
            a[++j]=a[i];
    }
    for(int i=0;i<=j;i++)
        cout<<a[i]<<endl;
    }
    return 0;
}
这个用集合比较快

#include<iostream>
#include<set>
using namespace std;
int main()
{
    int N,n;
    set<int> ss;
    while(cin>>N)     //多组数据
    {
        ss.clear();   //清除上一组数据的影响
     while(N--)
     {
         cin>>n;
         ss.insert(n);
     }
     for (set<int>::iterator it = ss.begin(); it != ss.end(); it++)
     {
            cout << *it << endl;
     }     
    }
    return 0;
}

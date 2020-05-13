#include<iostream>
#include<vector>
using namespace std;
int main()
{
    long m;
    vector<int> result;
    cin>>m;
    for(int x=2;x<=m;x++)
    {
        if(m%x==0)
        {
            m/=x;
            result.push_back(x);
            x--;//秒啊妙啊秒啊秒啊
        }
    }
    for(int i=0;i<result.size();i++)
    {
        cout<<result[i]<<" ";
    }
    return 0;
}

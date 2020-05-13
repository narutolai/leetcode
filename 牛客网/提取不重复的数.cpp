#就是把一个整数从左到右拆分。
#include<iostream>
#include<vector>
using namespace std;
int main()
{
    vector<bool> flag(10,false);
    vector<int>  result(10);
    int x,c,i=0;
    cin>>x;
    while(x){
        c=x%10;
        if(!flag[c])
        {
            flag[c]=true;
            result[i++]=c;
        }
        x/=10;
    }
    int pre=0,sum=0;
    for(int k=0;k<i;k++)
    {
        sum=result[k]+pre*10;
        pre=sum;
    }
    cout<<sum<<endl;
        return 0;
}

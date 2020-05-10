#include<iostream>
#include <string>
#include <math.h>
using namespace std;
int main()
{
    string str;

    while(cin>>str)
    {
        int sum=0;
        int size=str.size();
        for(int i=str.size()-1;i>=2;i--)
        {
            if(str[i]>='0'&&str[i]<='9')
               {
                   sum+=(str[i]-'0')*pow(16,size-i-1);
               }
             else if(str[i]>='A'&&str[i]<='F')
               {
                   sum+=(str[i]-'A'+10)*pow(16,size-i-1);
               }
               else 
               {
                   sum+=(str[i]-'a'+10)*pow(16,size-i-1);
               }   
        }
        cout<<'0'+sum-48<<endl;
     }
    return 0;
}

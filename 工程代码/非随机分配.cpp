非权重模拟
#include <iostream>
#include <vector>
#include<string>
#include <math.h>
using namespace std;
int main(int argc,char const *argv[])
{
	
	int a[4]={0,0,0,0};
	double perve[4]={0.1,0.2,0.2,0.5};
	int totalnum=5;
	while(1)
	{
		
		int index;
		double delta=INT_MAX;


		for(int j=0;j<4;j++)
		{
			a[j]++;
			
			double alpha=0;
			for(int i=0;i<4;i++)
			{		
				 alpha += pow((sqrt(a[i] / (double)totalnum) - sqrt(perve[i])), 2);
			}
			
			//cout<<"alpha: "<<alpha<<endl;
			if(alpha<delta)
			{
				delta=alpha;
				index=j;
			}
			a[j]--;
		}
		a[index]++;
		totalnum++;
		cout<<"index: "<<index<<endl;
		cout<<a[0]<<" "<<a[1]<<" "<<a[2]<<" "<<a[3]<<endl;
		cout<<"totalnum: "<<totalnum<<endl;
		if(totalnum==100)
			break;
	}
	return 0; 
}

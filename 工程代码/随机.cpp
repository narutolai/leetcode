#include <iostream>
#include <cstdlib>
#include <ctime>
#include<numeric>
#include <vector>

#define random(a,b) (rand()%(b-a)+a)
using namespace std;

struct cord
{
	int x;
	int y;
};


int main(int argc, char const *argv[])
{	

	int m=7;
	int n=10;
	int nums=25;
	vector<cord> vec(nums);
	vector<vector<bool>> visit(m+2,vector<bool>(n+2,false));
	//首先产生起始点坐标
	srand((int)time(0));  // 产生随机种子  把0换成NULL也行
	int temp=random(0, m); 
	cout<<"temp: "<<temp<<endl;
	vec[0].x=temp;
	vec[0].y=0;
	visit[temp+1][0+1]=true;
	

	int y=1;
	int used=1;
	int cur_x=temp;
	int cur_y=1;


	int last_way=1;
	int nx,ny,index;
	
	int horizontal_times=nums-n;
	cout<<"horizontal "<<horizontal_times<<endl;
	while(y<n-1)
	{	
		int way_flag=-1;
		
		//上一步往上走
		if(last_way==1)
		{
			int choice1[3][2]={{cur_x-1,cur_y},{cur_x,cur_y+1},{cur_x+1,cur_y}};
			 index=random(0,3);
			 if(index!=1)way_flag=1;
		
			 nx=choice1[index][0];
			 ny=choice1[index][1];
		}   //上一步往右走
		else if(last_way==2)
		{

			int choice2[2][2]={{cur_x,cur_y+1},{cur_x+1,cur_y}};
			index=random(0,2);

			if(index==1) way_flag=1;
			

			 nx=choice2[index][0];
			 ny=choice2[index][1];
		}//上一步往左走
		else if(last_way==0)
		{
			
			 int choice3[2][2]={{cur_x-1,cur_y},{cur_x,cur_y+1}};
			 index=random(0,2);
			 if(index==0) way_flag=1;
		
			 nx=choice3[index][0];
			 ny=choice3[index][1];
		}

		cout<<"  x: "<<nx<<" y:"<<ny<<endl;
		//出界重新选一次位置
		
		cout<<" index :"<<index<<" way_flag: "<<way_flag<<endl;


		if(nx<0||nx>m-1||ny<1){cout<<"  out bound"<<endl;continue;}
		
		if(way_flag==1)
			{
				horizontal_times--;
				if(horizontal_times<0)
					{
						cout<<"  can't move horizontal"<<endl;
						continue;
					}
				cout<<"<----> "<<" horizontal_times "<<horizontal_times<<endl;
			}
		else cout<<" | "<<endl; 

		vec[used].x=cur_x;
		vec[used].y=cur_y;

		cout<<"used"<<used<<endl;
		cout<<endl;
		visit[cur_x+1][cur_y+1]=true;
		used++;
		last_way=index;
		cur_x=nx;
		cur_y=ny;
		y=ny;		
	}

	vec[used].x=nx;
	vec[used].y=y;
	used++;

	int k=used;
	int dpd[m][n]={0};
	cout<<"used: "<<used<<endl;
	for(int i=0;i<used;i++)
	{
		dpd[vec[i].x][vec[i].y]=1;
		cout<<vec[i].x<<" "<<vec[i].y<<endl;
	}



	//如果还有剩余的真板子

	
	while(used<nums)
	{
		
		//随机选择之前的一个点
		int index=random(0,used);
		cout<<"random choice: "<<index<<endl;
		//选择该点4个方向的的
		int x_t=vec[index].x;
		int y_t=vec[index].y;
		cout<<"x_t: "<<x_t<<"y_t: "<<y_t<<endl;
		int d4[4][2]={{x_t+1,y_t},{x_t-1,y_t},{x_t,y_t+1},{x_t,y_t-1}};
		int a[4]={0};

		int tp=random(0,4);
		a[tp]=1;
		cout<<"tp"<<tp<<endl;

		//找到那个未被访问的点 且该点未越界
		//int time1=0; 位置不合法肯定继续找 访问数组就会出问题
		while(((d4[tp][0]<0||d4[tp][0]>m-1||d4[tp][1]<1||d4[tp][1]>n-1)||visit[d4[tp][0]+1][d4[tp][1]+1])&&accumulate(a,a+4,0)<4)
		{	
			
				cout<<"  visit[d4[tp][0]][d4[tp][1]]: "<<visit[d4[tp][0]+1][d4[tp][1]+1]<<endl;
				cout<<"  x: "<<d4[tp][0]<<"y: "<<d4[tp][1]<<endl;
				cout<<" accumulate(a,a+4,0) "<<accumulate(a,a+4,0)<<endl;

				tp=random(0,4);
				a[tp]=1;
				cout<<"  tp"<<tp<<endl;
				cout<<endl;
		}

		//如果最后出来的这个点 是可行的
		if(!visit[d4[tp][0]+1][d4[tp][1]+1]&&(d4[tp][0]>=0&&d4[tp][0]<=m-1&&d4[tp][1]>=1&&d4[tp][1]<=n-1))
			{
				cout<<" final tp: "<<tp<<endl;
			//然后在其上放置真板子
			visit[d4[tp][0]+1][d4[tp][1]+1]=true;
			vec[used].x=d4[tp][0];
			vec[used].y=d4[tp][1];
			used++;
		}
		else continue;
	}


	

for (int i=k;i<nums;++i)
{
	dpd[vec[i].x][vec[i].y]=1;
	cout<<vec[i].x<<" "<<vec[i].y<<endl;

}


	for(int i=0;i<m;i++)
		{for (int j=0;j<n;j++)
		{
			if(dpd[i][j]==1)
				cout<<dpd[i][j]<<" ";
			else cout<<"  ";
		}
		cout<<endl;
	}
	cout<<"normal out"<<endl;
	return 0;
}

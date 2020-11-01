#include <iostream>
#include <vector>
#include <set>
#include <time.h>
#include <algorithm>
using namespace std;

//排列
void Perm(int start, int end, vector<int> &a) {
    //得到全排列的一种情况，输出结果
    if (start == end) {
        for (int i = 0; i < end; i++)
            cout << a[i] << ' ';
        cout << endl;
        return;
    }
    for (int i = start; i < end; i++) {
        swap(a[start], a[i]);      //交换
        Perm(start + 1, end, a);   //分解为子问题a[start+1,...,end-1]的全排列
        swap(a[i], a[start]);      //回溯
    }
}

//组合 如果只有一段 那么就使用这个得到候选集
void combi(int pos, int cnt, uint32_t n, int k, vector<int>&a,vector<bool> &visited,vector<vector<int>>&result) 
{
    //已标记了k个数，输出结果
    if (cnt == k) 
    {
    	vector<int> temp;
        for (uint32_t i = 0; i < n; i++)
            if (visited[i]) temp.push_back(a[i]);
        result.push_back(temp);
        return;
    }

    //处理到最后一个数，直接返回
    if (pos == (int)n) return;

    //如果a[pos]没有被选中
    if (!visited[pos]) 
    {
        //选中a[pos]
        visited[pos] = true;
        //处理在子串a[pos+1, n-1]中取出k-1个数的子问题
        combi(pos + 1, cnt + 1, n, k, a,visited,result);
        //回溯
        visited[pos] = false;   
    }
    //处理在子串a[pos+1, n-1]中取出k个数的问题
    combi(pos + 1, cnt, n, k, a, visited,result);
}
//
void combi_of_multidis(vector<vector<int>> & m,vector<int> & temp,int i,vector<vector<int>> & result)
{
	if(i==(int)m.size()) 
		{
			result.push_back(temp);
			return;
		}
	for(int j=0;j<(int)m[i].size();j++)
		{
			temp.push_back(m[i][j]);
			i++;
			combi_of_multidis(m,temp,i,result);
			i--;
			temp.pop_back();
		}
}
//得到前一行的分段情况
void get_distance(vector<int>& line,vector<vector<int>>&piece)
{
	for(uint32_t i=0;i<line.size();)
	{
			
			if(line[i]==1)
			{	vector<int> temp;
				while(line[i]==1)
				{
					temp.push_back(i);
					i++;
				}
				if(temp.size()>0)
				piece.push_back(temp);
			}
			i++;
	}
}
//每多出一个真板子 就使用这个函数一次
void get_combine(vector<vector<int>> &origin,vector<vector<int>>&result,int width)
{

	for(uint32_t i=0;i<origin.size();i++)
		{	
		for(uint32_t j=0;j<origin[i].size();j++)
		{
			vector<int> temp_l=origin[i];
			vector<int> temp_r=origin[i];

			int left=temp_l[j]-1;
			int right=temp_r[j]+1;
			
			if(left>=0)
			temp_l.push_back(left);
			sort(temp_l.begin(),temp_l.end());

			if(right<width)
			temp_r.push_back(right);
			sort(temp_r.begin(),temp_r.end());

			result.push_back(temp_l);
			result.push_back(temp_r);
		}
		cout<<endl;
	}
}

//去重复
void duplicate(vector<vector<int>>& result)
{
	set<vector<int>> result_temp(result.begin(),result.end());
	result.assign(result_temp.begin(),result_temp.end());
}


//判断当前选择是否可行
bool isvalid(vector<vector<int>> &matrix,int i,vector<vector<int>> &piece,vector<vector<int>> &piece_cur)
{
	
	
	bool temp2=true;
	bool temp3=true;
	//下面一行 遍历每一个分段
	int width=matrix[0].size();
	//i-1层的每段的每个点要保证 4周相加大于1
	cout<<"step1"<<endl;

	for(uint32_t k=0;k<piece.size();k++)
	{

		for(uint32_t cur=0;cur<piece[k].size();cur++)
		{
				if((matrix[i][piece[k][0+cur]]+(piece[k][0+cur]-1>=0?matrix[i-1][piece[k][0+cur]-1]:0)+(piece[k][0+cur]+1<width?matrix[i-1][piece[k][0+cur]+1]:0)+(i-2>=0?matrix[i-2][piece[k][0+cur]]:1))<=1)
				{   temp2=false;
					break;
				}			
		}
		if(!temp2) break;
	}
	cout<<"step2"<<endl;
	//下面一行 遍历每一个分段
	//如果该连续段的下面至少出现了一个1 那么至少该段段检测是通过的
	for(uint32_t k=0;k<piece_cur.size();k++)
	{
		//区间内有1的就行了
		bool temp3_ =false;
		for(uint32_t cur=0;cur<piece_cur[k].size();cur++)
		{		

				
				if(matrix[i-1][piece_cur[k][0+cur]]==1)
				{   
					temp3_=true;
					break;
				}			
		}
		temp3 &=temp3_;
	}

	cout<<"fuck"<<endl;

	return temp2&temp3;
}

//回溯主体框架
void backtrace(vector<vector<int>> & matrix ,vector<int>&init,int i,bool &finish)
{
		

		cout<<"line: "<<i<<endl;
		//结束条件	
		int height=matrix.size();
		if(i==height){finish=true;return;}	
		
		//进入函数时 先计算前一行的区间段
		vector<int> line=matrix[i-1];
		int width=line.size();

		vector<vector<int>> piece;
		get_distance(line,piece);

		cout<<"	piece:st--et of preline: "<<i-1<<": ";
		for(uint32_t j=0;j<piece.size();j++)
			for(uint32_t k=0;k<piece[j].size();k++)
				cout<<piece[j][k]<<" ";
		cout<<endl;
		
		//获取当前行的真板个数
		int true_num=init[i];
		vector<vector<int>> result;

		cout<<"	piece size:"<<piece.size()<<endl;
		if(piece.size()==1)
		{
			vector<int> place;
			int st=piece[0][0];
			uint32_t len=piece[0].size();
			int et=piece[0][0+len-1];
			cout<<"	st and et: "<<st<<" "<<et<<endl;


			int st_=max(0,st-true_num+1);
			int et_=min(width,et+true_num-1);

			for(int j=st_;j<=et_;j++)
				place.push_back(j);
			//place是可选的坐标集合 需要在其中选全排列
			uint32_t num=place.size();
			vector<bool> visited(num,false);
			combi(0,0,num,true_num,place,visited,result);
			
		}
		else
		{
			//如果当前行的真板子数小于上一行分段数 那这个函数可以直接return了
			cout<<"true_num: "<<true_num<<endl;
			if(true_num<(int)piece.size()) return;
			//否则开始选
			vector<int> temp;
			combi_of_multidis(piece,temp,0,result);
			//如果当前行真板子数大于前一行分段数 那就要处理剩余真板子了
			if(true_num>(int)piece.size())
			{	
				cout<<"line:232"<<endl;
				int delta=true_num-piece.size();
				
				while(delta>0)
				{
					vector<vector<int>> result_;
					get_combine(result,result_,width);
					result=result_;
					delta--;
				}
				//只有这种情况需要去重的
				duplicate(result);
			}
		}

		//随机打乱
		srand(time(NULL));
		random_shuffle(result.begin(),result.end());

		cout<<"	combinetion you can choose:"<<endl;

		for(uint32_t j=0;j<result.size();j++)
			{
				for(uint32_t k=0;k<result[j].size();k++)
				cout<<result[j][k]<<" ";
				cout<<"    ";
			if(j%5==0)
			cout<<endl;
			}

			cout<<endl;

		for(uint32_t j=0;j<result.size();j++)
		{
			cout<<"	combie: "<<j<<" ";
			vector<int> tp=result[j];

			for(uint32_t l=0;l<tp.size();l++)
			{	 cout<<"  index: "<<tp[l]<<" ";
				matrix[i][tp[l]]=1;
			}

			cout<<endl;
			vector<int> line=matrix[i];
			vector<vector<int>> piece_cur;

			get_distance(line,piece_cur);

			for(uint32_t j=0;j<line.size();j++)
				cout<<line[j]<<" ";
			cout<<endl;

			cout<<"cur_line st---et:"<<endl;
			for(uint32_t j=0;j<piece_cur.size();j++)
			{
				for(uint32_t k=0;k<piece_cur[j].size();k++)
					cout<<piece_cur[j][k]<<" ";
				cout<<endl;
			}

			cout<<endl;

			if(!isvalid(matrix,i,piece,piece_cur)) 
				{
					cout<<"		not ok"<<endl;

					for(uint32_t l=0;l<tp.size();l++)
					{
						matrix[i][tp[l]]=0;
					}
					continue;
				}

			backtrace(matrix,init,i+1,finish);
			//找到一个解就返回
			if(finish) 
				return;

			for(uint32_t l=0;l<tp.size();l++)
			{
				matrix[i][tp[l]]=0;
			}
		}
}

int main()
{

		int m=11;
		int n=10;
		bool finish=false;
		vector<int> init={1,5,2,4,2,4,2,4,2,4,1};
		vector<vector<int>> matrix(m,vector<int>(n,0));
		int temp=5;
		matrix[0][temp]=1;
    
		backtrace(matrix,init,1,finish);
		cout<<"normal out"<<endl;
		for(uint32_t i=0;i<matrix.size(); i++)
		{
			for(uint32_t j=0; j<matrix[i].size();j++)
				cout<<matrix[i][j];

			cout<<endl;
		}
	return 0;
}



#include "test3.h"


//组合 如果只有一段 那么就使用这个得到候选集




/*
	这个函数是用来获取组合的 就是数学中的排列组合中的组合
	

*/
void CRandPath::combi(int pos, int cnt, int n, int k, vector<int>&a,vector<bool> &visited,vector<vector<int> >&result) 
{
    //已标记了k个数，输出结果
    if (cnt == k) 
    {
    	vector<int> temp;
        for (int i = 0; i < n; i++)
            if (visited[i]) 
            	temp.push_back(a[i]);
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
void CRandPath::combi_of_multidis(vector<vector<int> > & m,vector<int> & temp,int i,vector<vector<int> > & result)
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


/*
得到一行的连续区间坐标 
line是当前行的填入情况

piece是个二维数组，存储连续区间个数 以及每个区间的下标

*/
void CRandPath::get_distance(vector<int>& line,vector<vector<int> >&piece)
{
	for(int i=0;i<(int)line.size();)
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

/*
origin是多端区间组合后得到的可选组，这个函数负责在这个可选组中加一个板子
	比如origin中的一个 组合是  2  5 7 那么这个函就可以产生 


*/
void CRandPath::get_combine(vector<vector<int> > &origin,vector<vector<int> >&result,int width)
{

	//遍历所有的组合
	for(int i=0;i<(int)origin.size();i++)
		{	
			//取出当前组合每一个数
			
		for(int j=0;j<(int)origin[i].size();j++)
		{
			
			vector<int> temp_l=origin[i];
			vector<int> temp_r=origin[i];
			//将其减1和加1 
			int left=temp_l[j]-1;
			int right=temp_r[j]+1;
			
			//不越界 就加入
			if(left<width&&left>=0&&find(temp_l.begin(),temp_l.end(),left)==temp_l.end())
			{
				temp_l.push_back(left);// 2 5 7 衍生出 1 2 5 7
				sort(temp_l.begin(),temp_l.end());
				//然后把衍生出的结果放入result 
				result.push_back(temp_l);
			}
			


			if(right<width&&right>=0&&find(temp_r.begin(),temp_r.end(),right)==temp_r.end())
			{
				temp_r.push_back(right); //2 5 7 衍生出2 3 5 7
				sort(temp_r.begin(),temp_r.end());
				result.push_back(temp_r);
			}
			
			
			
			//简单的说就是遍历每一个左边在其左边和右边加1 不越界就加入
		}
	}
}

//去重复
void CRandPath::duplicate(vector<vector<int> >& result)
{
	set<vector<int>> result_temp(result.begin(),result.end());
	result.assign(result_temp.begin(),result_temp.end());
}


//判断当前选择是否可行
bool CRandPath::isvalid(vector<vector<int> > &matrix,int i,vector<vector<int> > &piece,vector<vector<int> > &piece_cur)
{
	
	
	bool temp2=true;
	bool temp3=true;
	//下面一行 遍历每一个分段
	int width=matrix[0].size();
	//i-1层的每段的每个点要保证 4周相加大于1
	cout<<"step1"<<endl;

	for(int k=0;k<(int)piece.size();k++)
	{

		for(int cur=0;cur<(int)piece[k].size();cur++)
		{
				if((matrix[i][piece[k][0+cur]]+(piece[k][0+cur]-1>=0?matrix[i-1][piece[k][0+cur]-1]:0)+(piece[k][0+cur]+1<width?matrix[i-1][piece[k][0+cur]+1]:0)+(i-2>=0?matrix[i-2][piece[k][0+cur]]:1))<=1)
				{   
					temp2=false;
					break;
				}			
		}
		if(!temp2) break;
	}
	cout<<"step2"<<endl;

	//当前层
	//如果该连续段的下面至少出现了一个1 那么至少该段段检测是通过的
	for(int k=0;k<(int)piece_cur.size();k++)
	{
		//区间内有1的就行了
		bool temp3_ =false;
		for(int cur=0;cur<(int)piece_cur[k].size();cur++)
		{		
				if(matrix[i-1][piece_cur[k][0+cur]]==1)
				{   
					temp3_=true;
					break;
				}			
		}
		temp3 &=temp3_;
	}

	return temp2&temp3;
}

//回溯主体框架
/*
matrix是待填充的矩阵，
init是每一行的真板子数，
i是代表进入到第几行了 因为第0行的真板子数一定是1，所有我们的i从1开始进入，
finish代表是否找到可行解 找到就停止所有的递归了


*/
void CRandPath::backtrace(vector<vector<int> > & matrix ,vector<int>&init,int i,bool &finish)
{


		//结束条件	
		int height=matrix.size();

		if(i==height){finish=true;return;}	
		
		cout<<"true_num: "<<init[i]<<endl;

		//进入函数时 先计算前一行的分段区间情况存放在piece中
		vector<int> line=matrix[i-1];
		int width=line.size();
		vector<vector<int> > piece;
		get_distance(line,piece);


		//打印调试信息而已
		cout<<"	piece:st--et of preline: "<<i-1<<": ";
		for(int j=0;j<(int)piece.size();j++)
			for(int k=0;k<(int)piece[j].size();k++)
				cout<<piece[j][k]<<" ";
		cout<<endl;
		//获取当前行的真板个数
		if(i>=(int)init.size()) return;
		int true_num=init[i];

		//这个result是用来获取当前行的可选择列表，获取这个result其实有点意思
		vector<vector<int> > result;
		result.reserve(500);
		cout<<"	piece size:"<<piece.size()<<endl;


		//
		/*
		如果前一行只有一个连续的区间段 分清区间段的个数很重要。
		*/
		if(piece.size()==1)
		{
			vector<int> place;

			//获取前一个区间段起始和终点下标
			int st=piece[0][0];
			int len=piece[0].size();
			int et=piece[0][0+len-1];
			cout<<"	st and et: "<<st<<" "<<et<<endl;


			//然后在结合当前行的真板子个数，我们就知道当前行可填入坐标的范围 
			int st_=max(0,st-true_num+1);
			int et_=min(width-1,et+true_num-1);

			//把可填入坐标范围填入place中 
			for(int j=st_;j<=et_;j++)
				place.push_back(j);

			//place是可选的坐标集合 需要在其中选全排列

			int num=place.size();

			vector<bool> visited(num,false);

			//然后产生组合 这个算法使用来产生组合的，存放再resul中
			combi(0,0,num,true_num,place,visited,result);
			
		}
		else//如果有多个连续的区间段 我们就要用另一种方法来思考怎么产生组合了
		{
			/*
			首先在这里我们要判断当前行的真板子数小于上一行分段数 那这个函数可以直接return了
			因为是要连通的，所以你前一行的每一个连续区间至少得分一个真板子吧，才可以保证连通有路可走啊。
			*/
			cout<<"true_num: "<<true_num<<endl;
			if(true_num<(int)piece.size()) return;

			//否则开始选
			vector<int> temp;
			//如果有多个区间，我们先让各个区间内的数都相互组合一次
			/*
				比如我有三个连续区间  分别是 1 2 3     4 5    6 7 8
				那么就先要产生 146 147  148.... 358 的这个组合 就是每一个区间各取一个数凑在一起，得到所有的组合 每个组和3个点
				也就是说先填掉3个点
			*/
			combi_of_multidis(piece,temp,0,result);
			//如果当前行真板子数大于前一行分段数 那就要处理剩余真板子了

			//然后还不够 如果当前行的真板子是5呢 那我们还要处理剩余的真板子，
			if(true_num>(int)piece.size())
			{	
				//剩余真板子数
				int delta=true_num-piece.size();
				
				//主要就是这个循环负责处理剩余的真板子
				while(delta>0)
				{
					vector<vector<int> > result_;
					//这个get_comine
					cout<<"deal with left borad: "<<delta<<endl;
					for(int k=0;k<(int)result.size();k++)
					{
						for(int h=0;h<(int)result[k].size();h++)
							cout<<result[k][h]<<" ";
						cout<<"    "<<endl;
						if(k%5==0)
							cout<<endl;
					} 

					get_combine(result,result_,width);
					result=result_;
					//填充一个真板子减少1
					delta--;
				}
				//填充是需要去重的 因为get_combie函数中可能会有重复的组合
				duplicate(result);
			}
		}



		//到这里 当前层的选择列表 result 就出来了
		//随机打乱 这个打不打乱都行
		srand(time(NULL));
		random_shuffle(result.begin(),result.end());
		cout<<"	combinetion you can choose:"<<endl;



		//调试信息
		for(int j=0;j<(int)result.size();j++)
			{
				for(int k=0;k<(int)result[j].size();k++)
				cout<<result[j][k]<<" ";
				cout<<"    ";
			if(j%5==0)
			cout<<endl;
			}

			cout<<endl;







		//现在进入主for循环开始回溯了
			cout<<" result size:"<<result.size()<<endl;

		for(int j=0;j<(int)result.size();j++)
		{
			cout<<"	combie: "<<j<<" ";
			//获取一个组合
			vector<int> tp=result[j];

			//然后在矩阵中填入1
			for(int l=0;l<(int)tp.size();l++)
			{	 cout<<"  index: "<<tp[l]<<" ";
				matrix[i][tp[l]]=1;
			}

			cout<<endl;
			vector<int> line=matrix[i];
			vector<vector<int> > piece_cur;

			//填完后获取当前行的分段区间
			get_distance(line,piece_cur);

			// //打印
			// for(int j=0;j<(int)line.size();j++)
			// 	cout<<line[j]<<" ";
			// cout<<endl;
			// cout<<"cur_line st---et:"<<endl;
			// for(int j=0;j<(int)piece_cur.size();j++)
			// {
			// 	for(int k=0;k<(int)piece_cur[j].size();k++)
			// 		cout<<piece_cur[j][k]<<" ";
			// 	cout<<endl;
			// }
			// cout<<endl;
			/*
			然后判断这样填 或者说这个组合是否可行 
			这给而判断函数其实很想了很久  我就是在其中发现判断位置可不可行要以连续段来思考，不能看一个板子		
			*/
			if(!isvalid(matrix,i,piece,piece_cur)) 
				{
					cout<<"		not ok"<<endl;
					//如果不可行就要撤消选择
					for(int l=0;l<(int)tp.size();l++)
					{
						matrix[i][tp[l]]=0;
					}
					continue;
				}

				//如果可行就到下一行去
			cout<<"ok :"<<j<<endl;

			for(int l=0;l<(int)tp.size();l++)
			{	 cout<<" ok index: "<<tp[l]<<" ";
				matrix[i][tp[l]]=1;
			}
			backtrace(matrix,init,i+1,finish);
			//找到一个解就返回
			if(finish) 
				return;

			//撤消选择
			for(int l=0;l<(int)tp.size();l++)
			{
				matrix[i][tp[l]]=0;
			}
		}

}


							//n是10  m为12
void CRandPath::RandFlour2(int n,int m,vector<int> & init,vector<cs::Coord> & vec)
{

		vector<vector<int> > matrix(m,vector<int>(n,0));
		srand((int)time(0));
    	int temp = random(0,n);
    	

		
		matrix[0][temp]=1;
		
		bool finish=false;
		backtrace(matrix,init,1,finish);
		cout<<"normal out"<<endl;

		cs::Coord coord;
		for(int i=0;i<(int)matrix.size(); i++)
		{
			for(int j=0; j<(int)matrix[i].size();j++)
				{
					cout<<matrix[i][j];
					if(matrix[i][j]==1)
					{
						coord.x=i;
						coord.y=j;
						vec.push_back(coord);
					}
				}
			cout<<endl;
		}

		cout<<temp<<endl;
		cout<<endl;

		// for(uint32_t i=0;i<vec.size();i++)
		// 	cout<<vec[i].x<<" "<<vec[i].y<<endl;
}


int main()
{

		int m=11;
		int n=10;
		
		vector<int> init{1,2,3,4,5,6,5,4,3,2,1};
		
    	CRandPath randpathmaker;
    	vector<cs::Coord> vec;
    	
			
		randpathmaker.RandFlour2(n,m,init,vec);
			
		
		cout<<"normal out"<<endl;
	return 0;
}




// 其实是一个基本的回溯框架
// backtrace(i)
// {
// 	if(达到条件){return;}

// 	for(可选择列表)
// 	{
// 		做出选择；
// 		判断选择是否可行；
// 		如果不可行，continue;
// 		backtrace(i+1);
// 		撤销选择;
// 	}
// }
// 主要就是在解空间搜索一个可行解 ，我们要求找到一个解就返回
// 对于本任务，
// 1.你要做出的选择就是你应该在当前行的哪些点填入1，
// 2.选择列表就是在可行范围内能填的坐标组合，但是不代表可行，得到所有的候选组合是很重要的，不然可能会漏解
// 3.是否可行就要兼顾到当前行和前一行的分段区间了情况了
// 4.这个算法最难的其实是第2点和第3点

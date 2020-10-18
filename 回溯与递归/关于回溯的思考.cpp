int j=0;
int all=0;
int flag=0;
void backtrace1()
{
	all++;
	if(j==3){flag=1;return;}
	for(int i=0;i<2;i++)
	{
		j++;
		cout<<"loop: "<<i<<endl;
		cout<<"j: "<<j<<endl;
		backtrace1();
		if(flag)return;
		j--;
	}
}
void backtrace2()
{
	all++;
	if(j==4){flag=1;return;}
		int size=st.size();
		st+="-->";
		cout<<st<<endl;
		j++;
		backtrace2();
		//if(flag)return;
		//st.erase(size,3);
		//cout<<st<<" ： "<<endl;
		//j--;
		if(flag)return;
		//int size=st.size();
		//st+="-->";
		//cout<<st<<" ： "<<endl;
		//j++;
		backtrace2();
		if(flag)return;
		st.erase(size,3);
		cout<<st<<endl;
		j--;
	
}

1引入一个问题，深度优先搜索只是一种遍历方式，针对具体的任务，我们在编写代码的时，有以下行为：

1)要得到多个满足条件的可行解，这样很大可能要遍历所有的节点（或者说尝试所有的选择;
2)只需要得到一个满足条件的可行解，这样达到条件后就停止访问了;
3)如果是最优解呢，还是要穷尽所有尝试；

这三种方法都可以采取剪枝策略来减少递归函数的调用。


第7行是返回条件，第14行是针对2）的解决方法,设置了一个全局变量flag，当有一个满足条件的解时(第7行),其他函数退出后就没必要再做选择了(紧跟着13行函数结束后退出就是了)
如果要找到所有j==3的解,那么不需要第14行
all表示backtrace()被调用的总次数；

backtrace2()和backtrace1()是一样的只不过把那个for循环给展开了，看backtrace2()中展开的后注释的部分，
此外求出解时，递归函数的调用都是一样的，就是要在31行和37行后面都加上if(flag)return;这个判断返回语句,

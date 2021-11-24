#include <iostream>
#include <vector>
#include <numeric>
#include <unistd.h>
using namespace std;

class GAME
{
public:
	GAME(int m_, int n_, int k_) : m(m_), n(n_), k(k_)
	{
		std::vector<char> temp;
		for (int i = 0; i < n; i++)
			temp.push_back('#');
		for (int i = 0; i < k; i++)
			m_vector.push_back(temp);

		std::vector<char> temp1;
		for (int i = 0; i < n; i++)
			temp1.push_back(' ');
		for (int i = k; i < m; i++)
			m_vector.push_back(temp1);

		for (int i = k; i < m; i++)
		{
			m_vector[i][0] = '|';
			m_vector[i][n - 1] = '|';
		}
		for (int i = 1; i < n - 1; i++)
			m_vector[m - 1][i] = '-';

		//初始点
		m_vector[m - 1][n / 2] = '#';
		old_x = m - 1;
		old_y = n / 2;
		mod = m * k * 10;
		reset_time = 0;
	}
	~GAME()
	{
	}

private:
	int m;
	int n;
	int k;
	int mod;
	int old_x; //前一帧坐标
	int old_y;
	int new_x; //当前帧坐标
	int new_y;
	int index = 0;	  //方向索引
	int sum_step = 1; //累积步数 我们使用这个来判断是否需要退出
	int reset_time;	  //重置次数
	//每一步可以走的4个方向
	int way[4][2] = {{-1, 1}, {1, -1}, {1, 1}, {-1, -1}};
	std::vector<vector<char>> m_vector;

	//处理前一帧画面.
	void dealPreFrame()
	{
		m_vector[old_x][old_y] = ' ';
		if (old_x == m - 1)
		{
			m_vector[old_x][old_y] = '-';
		}
		else if ((old_y == n - 1 || old_y == 0) && old_x >= k)
		{
			m_vector[old_x][old_y] = '|';
		}
	}

	//确定下一步方向
	void dealNextWay()
	{
		//遇到4个顶点 以及边界时 下一步应该走的方向
		if (old_x == m - 1 && old_y == 0) //左下角
		{
			index = 0;
		}
		else if (old_x == m - 1 && old_y == n - 1) //右下角
		{
			index = 3;
		}
		else if (old_x == 0 && old_y == 0) //左上角
		{
			index = 2;
		}
		else if (old_x == 0 && old_y == n - 1) //右上角
		{
			index = 1;
		}
		else if (old_x == m - 1)
		{
			if (index == 0)
			{
				index = 0;
			}
			else if (index == 2)
			{
				index = 0;
			}
			else if (index == 1)
			{
				index = 3;
			}
		}
		else if (old_x == 0)
		{
			if (index == 3)
			{
				index = 1;
			}
			else if (index == 0)
			{
				index = 2;
			}
		}
		else if (old_y == 0)
		{
			if (index == 1)
			{
				index = 2;
			}
			else if (index == 3)
			{
				index = 0;
			}
		}
		else if (old_y == n - 1)
		{
			if (index == 0)
			{
				index = 3;
			}
			else if (index == 2)
			{
				index = 1;
			}
		}
	}
	//确定当前帧
	void dealCurFrame()
	{
		new_x = old_x + way[index][0];
		new_y = old_y + way[index][1];
		if (m_vector[new_x][new_y] == '#')
		{
			if (index == 0)
			{
				index = 2;
			}
			else if (index == 1)
			{
				index = 3;
			}
			else if (index == 2)
			{
				index = 0;
			}
			else if (index == 3)
			{
				index = 1;
			}
		}
		else
		{
			m_vector[new_x][new_y] = '#';
		}
	}
	void change()
	{
		dealPreFrame();
		dealNextWay();
		dealCurFrame();
		//新旧坐标 赋值
		old_x = new_x;
		old_y = new_y;
	}

	void showFrame()
	{
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cout << m_vector[i][j];
			}
			cout << endl;
		}
		cout << "x: " << new_x << "  y: " << new_y << endl;
		cout << "steps: " << sum_step << " mod：" << mod << " reset_time: " << reset_time << "  # count: " << count << endl;
	}
	int count = 0;
	bool judgestop()
	{
		count = 0;
		for (int i = 0; i < k; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (m_vector[i][j] == '#')
					count++;
			}
		}
		return count == 1; //
	}

public:
	void mainLoop()
	{
		while (1)
		{
			usleep(50000);
			change();
			showFrame();
			sum_step++;
			if (sum_step % max(mod, m * k) == 0) //每走mod步（不能小于m,且mod 慢慢减小） 我们判断一下是否要退出
			{
				reset_time++;
				mod = mod - mod / 10;
				if (!judgestop())
				{
					m_vector[new_x][new_y] = ' ';
					if (new_x == m - 1)
					{
						m_vector[new_x][new_y] = '-';
					}
					else if ((new_y == n - 1 || new_y == 0) && new_x >= k)
					{
						m_vector[new_x][new_y] = '|';
					}
					old_x = m - 1;
					old_y = rand() % n; //重置一个随机出生点
					index = 0;
				}
				else
				{
					cout << "game over" << endl;
					break;
				}
			}
		}
	}
};

int main()
{
	//表示创建m*n的矩阵 其中前k行是砖块，我们的砖块遇到边界或者砖块会45°角反弹，遇到砖块会把砖块消去
	GAME gm(10, 35, 5);
	gm.mainLoop();
	return 0;
}

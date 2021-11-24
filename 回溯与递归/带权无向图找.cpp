//给一个带权无向图，已知整数k，在图中路径长度为k的路径中找到权值最小的那条。

#include <iostream>
#include <math.h>
#include <limits.h>
#include <vector>
    using namespace std;

int dfs(vector<vector<int>> &edge, int k, int row, vector<bool> &visit)
{
    if (k <= 0)
    {
        return 0;
    }
    int weight_ = INT_MAX;
    bool find = false;
    visit[row] = true; //当前点已访问 row--->i
    for (int i = 0; i < (int)edge[row].size(); i++)
    {
        if (edge[row][i] > 0 && !visit[i]) //该点可达且未被访问过，进入该点 取出权重
        {
            int weight = edge[row][i]; //点row至点i的权重
            //这句话把遍历树打印出来了 方便理解
            cout << k << "step: " << row + 1 << "->" << i + 1 << ": " << weight << endl;

            visit[i] = true;
            find = true;
            k--;
            weight_ = min(weight_, weight + dfs(edge, k, i, visit));

            visit[i] = false; //回退
            k++;
        }
    }

    if (find == false) //如果已经找不到可用点，但是k还大于0，则返回一个很大的数，让这条路径不可用  ，
    {
        cout << "cant't find available point" << endl;
        return 10000;
    }

    return weight_;
}

void findpath(vector<vector<int>> &edge, int k)
{

    int pathsum = INT_MAX;
    int index = -1;
    for (int i = 0; i < (int)edge.size(); i++)
    {
        cout << "from point " << i + 1 << " traversal" << endl;
        vector<bool> visit((int)edge.size(), false);

        int cursum = dfs(edge, k, i, visit);
        cout << "cur min pathsum:" << cursum << endl;

        if (cursum < pathsum)
        {
            pathsum = cursum;
            index = i + 1;
        }
        cout << endl;
        cout << endl;
    }

    cout << "minimum pathsum is :" << pathsum << "  path begin point is :" << index << endl;
}

int main(int argc, char const *argv[])
{
    /*
        两种初始化方式随便选一种
        int m;
        cout<<"输入顶点个数";
        cin>>m;
        int k;
        cout<<"输入路径长度";        
        int edge[m][m];
        cout<<"输入权重";
        for(i=0;i<m;i++) 
            for(j=0;j<m;j++)
                cin>>edge[i][j];
        
        */
    vector<vector<int>> edge = {
        {0, 0, 1, 0, 0, 2, 3},
        {0, 0, 6, 0, 0, 4, 0},
        {1, 6, 0, 0, 2, 0, 0},
        {0, 0, 0, 0, 1, 5, 0},
        {0, 0, 2, 1, 0, 4, 0},
        {2, 4, 0, 5, 4, 0, 7},
        {3, 0, 0, 0, 0, 7, 0},
    };
    //这里我假设k为3了
    findpath(edge, 3);
}

设想有个机器人坐在一个网格的左上角，网格 r 行 c 列。机器人只能向下或向右移动，但不能走到一些被禁止的网格（有障碍物）。
设计一种算法，寻找机器人从左上角移动到右下角的路径。

示例 1:

输入:
[
  [0,0,0],
  [0,1,0],
  [0,0,0]
]
输出: [[0,0],[0,1],[0,2],[1,2],[2,2]]
解释: 
输入中标粗的位置即为输出表示的路径，即
0行0列（左上角） -> 0行1列 -> 0行2列 -> 1行2列 -> 2行2列（右下角）
/*
关于为什么很多人会超时。。。
dfs 的时候加一个 visited 标识一般是为了防止死循环，但这个题目只能向右向下走，所以不会死循环，所以很多人就不加 visited 了。
但其实这个题目仍然需要 visited 标识，因为我们可以通过不同的路径到达同一个位置：比如身处位置 (0,0) 时，
可以通过"先右再下"和“先下再右”两种方式到达 (1,1)。
使用 visited 就可以确保那些“已被试过无法到达目标”的位置不会再次被尝试，从而提升效率，避免超时。
*/

class Solution {
public: //动态规划了
    vector<vector<int>> result;
    bool flag=true; //设置一个标志是否还需遍历
    void  backtrace(vector<vector<int>>& obstacleGrid,int x,int y ,vector<vector<int>>& visited,vector<vector<int>>& buffer)
    {
        int m=obstacleGrid.size();
        int n=obstacleGrid[0].size();
        
        if(!flag) return;                   //已经探寻到终点了返回
        if(x>m-1||y>n-1) return ;           //越界返回
        if(obstacleGrid[x][y]==1) return;   //障碍物返回
        if(visited[x][y]==1) return ;       //已经访问过返回。
            
        visited[x][y]=1;
        if(x==0&&y==0)buffer.push_back({0,0});
        if(x==m-1&&y==n-1)                  //到达终点
        {
            flag=false;
            result=buffer;
            return;
        }

        buffer.push_back({x,y+1});                
        backtrace(obstacleGrid,x,y+1,visited,buffer); //向右边
        buffer.pop_back();

        buffer.push_back({x+1,y});
        backtrace(obstacleGrid,x+1,y,visited,buffer);  //向下边
        buffer.pop_back();

    }
    vector<vector<int>> pathWithObstacles(vector<vector<int>>& obstacleGrid) {
    
    int m=obstacleGrid.size();
    int n=obstacleGrid[0].size();
    
    vector<vector<int>> visited(m,vector<int>(n,0));
    vector<vector<int>> buffer;
    backtrace(obstacleGrid,0,0,visited,buffer);
        return result;
    }
};

class Solution {
public:
    //广度优先搜索
    int get(int x)
    {
        int res=0;
        while(x){
            res+=x%10;
            x/=10;
        }
        return res;
    }
    //深度优先搜索
    int movingCount(int m, int n, int k) {
        if (!k) return 1;
        vector<vector<int> > vis(m, vector<int>(n, 0));
        int ans = 1;
        vis[0][0] = 1;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if ((i == 0 && j == 0) || get(i) + get(j) > k) continue;
                // 边界判断
                if (i - 1 >= 0) vis[i][j] |= vis[i - 1][j];
                if (j - 1 >= 0) vis[i][j] |= vis[i][j - 1];
                ans += vis[i][j];
            }
        }
        return ans;
    }
    //广度优先搜索
    int movingCount(int m, int n, int k) {
          if(!k) return 1;
          queue<pair<int,int>> q;
          int dx[2]={0,1};
          int dy[2]={1,0};
          vector<vector<int>> visit(m,vector<int>(n,0));
          q.push(make_pair(0,0));
          visit[0][0]=1;
          int ans=1;
          while(!q.empty())
          {
              auto [x,y]=q.front();
              q.pop();
                for(int i=0;i<2;i++)
                {
                    int tx=dx[i]+x;
                    int ty=dy[i]+y;
                    if(tx<0||ty<0||tx>m-1||ty>n-1||visit[tx][ty]||get(tx)+get(ty)>k) continue;
                    q.push(make_pair(tx,ty));
                    visit[tx][ty]=1;
                    ans++;
                }
          }
          return ans;
    }
};

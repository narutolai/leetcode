// 已知一个 NxN 的国际象棋棋盘，棋盘的行号和列号都是从 0 开始。即最左上角的格子记为 (0, 0)，最右下角的记为 (N-1, N-1)。 

// 现有一个 “马”（也译作 “骑士”）位于 (r, c) ，并打算进行 K 次移动。 

// 如下图所示，国际象棋的 “马” 每一步先沿水平或垂直方向移动 2 个格子，然后向与之相垂直的方向再移动 1 个格子，共有 8 个可选的位置。

// 现在 “马” 每一步都从可选的位置（包括棋盘外部的）中独立随机地选择一个进行移动，直到移动了 K 次或跳到了棋盘外面。

// 求移动结束后，“马” 仍留在棋盘上的概率。

 class Solution
{
public:
    //从递归到动态规划，动态规划就是一个三维物体一层一层网上叠
    //果然超时了哈哈哈
    double dfs(int N, int K, int step, int i, int j)
    {
        if (i < 0 || j < 0 || i > N - 1 || j > N - 1)
            return 0; //越界返回
        if (step == K)
            return 1; //
        double res = 0;
        res += dfs(N, K, step + 1, i - 1, j - 2); //递归地走每一条子路径
        res += dfs(N, K, step + 1, i - 2, j - 1);
        res += dfs(N, K, step + 1, i - 2, j + 1);
        res += dfs(N, K, step + 1, i - 1, j + 2);
        res += dfs(N, K, step + 1, i + 1, j + 2);
        res += dfs(N, K, step + 1, i + 2, j + 1);
        res += dfs(N, K, step + 1, i + 2, j - 1);
        res += dfs(N, K, step + 1, i + 1, j - 2);
        return res / 8.0; //返回概率
    }

    //dp[k][i][j] 表示走k步落在(i,j)处的概率
    //转移方程就是从k-1层的8个位置加起来的和除以8
    double knightProbability(int N, int K, int i, int j)
    {
        // size_t N=static_cast<size_t>(P);
        //创建两个dp数组一个pre 一个cur
        vector<vector<double>> dp(N, vector<double>(N, 0));
        dp[i][j] = 1;
        vector<vector<double>> pre;
        for (int k = 0; k < K; k++)
        {
            pre = dp;
            for (int i = 0; i < N; i++)
                for (int j = 0; j < N; j++)
                {
                    double D1 = (i >= 1 && j >= 2) ? pre[i - 1][j - 2] : 0;
                    double D2 = (i >= 2 && j >= 1) ? pre[i - 2][j - 1] : 0;
                    double D3 = (i >= 2 && j < N - 1) ? pre[i - 2][j + 1] : 0;
                    double D4 = (i >= 1 && j < N - 2) ? pre[i - 1][j + 2] : 0;
                    double D5 = (i < N - 1 && j >= 2) ? pre[i + 1][j - 2] : 0;
                    double D6 = (i < N - 2 && j >= 1) ? pre[i + 2][j - 1] : 0;
                    double D7 = (i < N - 2 && j < N - 1) ? pre[i + 2][j + 1] : 0;
                    double D8 = (i < N - 1 && j < N - 2) ? pre[i + 1][j + 2] : 0;
                    dp[i][j] = (D1 + D2 + D3 + D4 + D5 + D6 + D7 + D8) / 8.0;
                }
        }
        double res = 0;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
            {
                res += dp[i][j];
            }
        return res;
    }
};

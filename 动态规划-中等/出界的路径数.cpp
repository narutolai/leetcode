三维矩阵的动态规划，在一个m*n的网格中有一个球位于x,y处，然后该球可以走N步，问几种使得球出界的方法。
算法：
这种方法的思想是，如果我们能够在 x 次移动中到达某个位置，我们可以在 x+1 次移动中到达它的所有相邻位置。
基于这个想法，我们利用一个二维 dp数组来存储可以到达特定位置的方法的数量。dp[i][j] 是指在特定的移动次数下，可达到 (i,j) 位置的方式数。
如果当前 dp 数组存储了使用 x-1 次移动可以达到各种位置的方式的数量，为了确定使用 x移动可以达到位置 (i,j) 的方式的数量，我们需要将更新 dp 为 $$dp[i][j] = dp[i-1][j] + dp[i+1][j] + dp[i][j-1] + dp[i][j+1]$$ 注意边界条件。因为我们可以从四个相邻位置中的任意一个位置达到位置 (i,j) 并且 x 次移动中达到指数 (i,j)(i,j) 的总方法数是 x-1x−1 移动中达到相邻位置的方法的总和。
如果我们改变 dpdp 数组，有一些情况将对应于 x-1x−1 次移动，更新的 dp 将对应于 xx 移动。因此，我们需要找到解决这个问题的方法。我们使用临时二维数组 temp 来存储x 移动的更新结果，而不是更新当前（x）移动的 dp 数组，使用与 x-1 次移动对应的 dp 数组获得的结果。在所有位置的所有 dp 都考虑了xx 移动之后，我们基于 temptemp 更新 dpdp 数组。因此，dpdp 现在包含对应于 xx 移动的所有情况。
因此，我们首先考虑零移动，我们对其进行初始输入 dp[x][y]=1dp[x][y]=1,((x,y)(x,y) 是初始位置），因为我们只能在零移动中达到这个位置。然后，我们将移动次数增加到 1，并适当地更新所有 dpdp。对于从 1 到 n 的所有可能移动，我们都这样做。
为了更新 countcount，它标识出界的路径数，我们只需要在到达边界时执行更新。我们将计数更新为 count=count+dp[i][j]count=count+dp[i][j]，其中 (i,j)(i,j) 对应于其中一个边界。但是，如果 (i,j)(i,j) 同时是多个边界的一部分，我们需要多次添加 dp[i][j]dp[i][j] 乘以 (i,j)(i,j) 所属的边界数。
在完成所有 NN 次移动之后，countcount 将给出所需的结果。


class Solution{
public:
    int findPaths(int m, int n, int N, int i, int j) {
       int mod=1e9+7;
       if(N==0) return 0;
vector<vector<vector<unsigned long long int>>> dp(m + 2, vector<vector<unsigned long long int>>(n + 2, vector<unsigned long long int>(N + 1, 0)));
//初始化最底层矩形的边
//其实弄个二维的也可以  
//边界条件
for (int i = 0; i <= m + 1; i++) {
        dp[i][0][0] = 1; 
        dp[i][n + 1][0] = 1;
    }
    for (int i = 0; i <= n + 1; i++) {
        dp[0][i][0] = 1;
        dp[m + 1][i][0] = 1;
    }
    
    for (int k = 1; k <= N; k++) {
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
               //移动K次能到达的位置是K-1次的相邻位置
                dp[i][j][k] = (dp[i - 1][j][k - 1] + dp[i + 1][j][k - 1] + dp[i][j - 1][k - 1] + dp[i][j + 1][k - 1]) % mod;
            }
        }
    }
    int sum = 0;
    for (int k = 1; k <= N; k++) {
        sum = (sum + dp[i + 1][j + 1][k]) % mod;
    }
    return sum;
    }
};

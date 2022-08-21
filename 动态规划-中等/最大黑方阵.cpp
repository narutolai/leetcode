
//就是找出边长全黑的最大正方形 。返回其左上角坐标 r,c和 边长 size。  如果size一样就返回r更小的 如果r一样返回c更小的。

class Solution
{
public:
  vector<int> findSquare(vector<vector<int>> &matrix)
  {
    int m = matrix.size();
    int n = matrix[0].size();
    vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(2, 0)));

    int r = -1;
    int c = -1;
    int size = -1;

    for (int i = 0; i < m; i++)
      for (int j = 0; j < n; j++)
      {
        if (matrix[i][j] == 1) //当前位置为1
        {
          dp[i][j][0] = 0;
          dp[i][j][1] = 0;
        }
        else //当前位置为0
        {
          dp[i][j][0] = (j - 1 < 0 ? 0 : dp[i][j - 1][0]) + 1; //水平方向上连续0的个数
          dp[i][j][1] = (i - 1 < 0 ? 0 : dp[i - 1][j][1]) + 1; //垂直方向上连续0的个数

          int size_ = min(dp[i][j][0], dp[i][j][1]); //取出最小值假设的为子方阵边长
          //这个判断很关键
          if (dp[i - size_ + 1][j][0] >= size_ && dp[i][j - size_ + 1][1] >= size_) //如果该子方阵真的存在
          {
            if (size_ > size) //如果子方阵更大 就要更新坐标和size
            {
              size = size_;
              r = i - size + 1;
              c = j - size + 1;
            }
            else if (size_ == size) //如果大小一样
            {
              if (i - size + 1 < r)
              {
                r = i - size + 1;
                c = j - size + 1;
              }
              else if (i - size + 1 == r) //如果r一样
              {
                c = min(j - size + 1, c); //取c最小的
              }
            }
          }
        }
      }
    if (size != -1)
      return {r, c, size};
    else
      return {};
  }
};

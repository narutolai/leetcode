// 给定一个整数数组 A，返回 A 中最长等差子序列的长度。

// 回想一下，A 的子序列是列表 A[i_1], A[i_2], ..., A[i_k] 其中 0 <= i_1 < i_2 < ... < i_k <= A.length - 1。
// 并且如果 B[i+1] - B[i]( 0 <= i < B.length - 1) 的值都相同，那么序列 B 是等差的。

// 示例 1：

// 输入：[3,6,9,12]
// 输出：4
// 解释：
// 整个数组是公差为 3 的等差数列。
// 示例 2：

// 输入：[9,4,7,2,10]
// 输出：3
// 解释：
// 最长的等差子序列是 [4,7,10]。
// 示例 3：

// 输入：[20,1,15,3,10,5,8]
// 输出：4
// 解释：
// 最长的等差子序列是 [20,15,10,5]。

//这个题就是多出了一个diff公差维度。
class Solution
{
public:
    //我不想管你公差是多少 我就想找出最长的等差子序列。
    //dp[i][j]表示公差为i 到j的最长等差数列
    int longestArithSeqLength(vector<int> &A)
    {
        int size = A.size();
        int maxlen = 0;

        //dp[i]以i为终点的等差数列       <公差, 长度>
        unordered_map<int, unordered_map<int, int>> dp;

        for (int i = 1; i < size; i++)
            for (int j = 0; j < i; j++)
            {
                int dif = A[i] - A[j];

                //如果以j为终点,公差为dif序列存在
                if (dp[j][dif] > 0) //那么以i为终点 公差为dif的最大长度就取其中的max
                    dp[i][dif] = max(dp[j][dif] + 1, dp[i][dif]);

                //如果该公差之前没有
                if (!dp[i][dif])
                    dp[i][dif] = 2; //就新录入
                
                maxlen = max(maxlen, dp[i][dif]);
            }
        return maxlen;
    }
};
//我靠 这个题目没有规定公差为多少 之前做了一道题目是有公差的
//也是oN的平方的啊
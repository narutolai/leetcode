// 给定一个非负整数 num。对于 0 ≤ i ≤ num 范围中的每个数字 i ，计算其二进制数中的 1 的数目并将它们作为数组返回。

// 示例 1:

// 输入: 2
// 输出: [0,1,1]
// 示例 2:

// 输入: 5
// 输出: [0,1,1,2,1,2]

//也可以使用动态规划 偶数：dp[i]=dp[i/2] 奇数 dp[i]=dp[i-1]+1;
class Solution
{
public:
    vector<int> countBits(int num)
    {
        vector<int> result;
        result.resize(num + 1, 0);
        //动态规划这个方法 可以把 1~num 之间每一个数的二进制1的个数都算出来，
        //使用动态规划 时间复杂度为 n 空间复杂度为 n  使用上面的方法 时间复杂度为n2
        //如果你直接算一个数的，那么使用动态规划 和 上面那个方法相比 时间复杂度为n 但是动态规划空间复杂度为n,
        for (int i = 0; i <= num; i++)
        {
            if (i % 2)
                result[i] = result[i - 1] + 1;
            else
                result[i] = result[i / 2];
        }
        return result;
    }
};
//这个时间复杂度有n^2啊 还是使用动态规划吧
//遍历次数 2
//奇数的比特1是前一个数加1 
//偶数的比特1和其一半相等
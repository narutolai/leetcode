给定一个非负整数 num。对于 0 ≤ i ≤ num 范围中的每个数字 i ，计算其二进制数中的 1 的数目并将它们作为数组返回。

示例 1:

输入: 2
输出: [0,1,1]
示例 2:

输入: 5
输出: [0,1,1,2,1,2]


//也可以使用动态规划 偶数：dp[i]=dp[i/2] 奇数 dp[i]=dp[i-1]+1;  
class Solution {
public:
    int countones(int x)
    {   int i=0;
        while(x)
        {
            x&=(x-1);
            i++;
        }
        return i;
    }
    vector<int> countBits(int num) {
        vector<int> result;
        result.resize(num+1);
        for(int i=0;i<=num;i++)
        {
         result[i]=countones(i);
        }
        return result;
    }
};

// 给定一个非负整数 num。对于 0 ≤ i ≤ num 范围中的每个数字 i ，计算其二进制数中的 1 的数目并将它们作为数组返回。

// 示例 1:

// 输入: 2
// 输出: [0,1,1]
// 示例 2:

// 输入: 5
// 输出: [0,1,1,2,1,2]

class Solution
{
public:
    //统计一个数中1的个数的一个方法是n&=(n-1) 的次数，这个运算每做一次都可以产生一个1
    //换句话说n的1个数和n&n-1的个数相差1 建立dp
    vector<int> countBits(int num)
    {
        vector<int> dp(num + 1);
        dp[0] = 0;
        for (int i = 1; i < num + 1; i++)
            dp[i] = dp[i & (i - 1)] + 1;    
        return dp;
    }
};

// 卧槽这个想法秒啊
// 很简单啊，不用多说，设dp[i]为i的二进制形式的1的个数，i是奇数时，dp[i]=dp[i-1]+1,因为i是在i-1的二进制数上加了个1啊；
// i是偶数时，dp[i]=dp[i/2],因为i就是把i/2往左移（是数左移，末尾补0）得到的，所以1的个数没变

// 1  001
// 2  010
// 3  011
// 4  100

class Solution
{
public:
    vector<int> countBits(int num)
    {
        vector<int> dp(num.size() + 1);
        dp[0] = 0;
        for (int i = 1; i <= num; i++)
        {
            if(i%2)//奇数
            {
                dp[i]=dp[i-1]+1;
            }
            else
            {
                dp[i]=dp[i/2];
            }
        }
        return dp;
    }
};
//遍历次数1
给定一个正整数 n，将其拆分为至少两个正整数的和，并使这些整数的乘积最大化。 返回你可以获得的最大乘积。

示例 1:

输入: 2
输出: 1
解释: 2 = 1 + 1, 1 × 1 = 1。
示例 2:

输入: 10
输出: 36
解释: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36

这数学推导是真的牛皮

class Solution {
public:
    int integerBreak(int n)
    {
            /*vector<int> dp(n+1);
            dp[1]=1;
            for(int i=2;i<=n;i++)
            for(int j=1;j<i;j++)
            {
                dp[i]=max(dp[i],max(dp[j],j)*(i-j));
            }
            return dp[n];
            */
            //通过数学推导出把数均分时其值可以最大，接近e我擦
            if(n<=3) return n-1;
            int x=n/3,y=n%3;
            if(y==0) return pow(3,x); //余数为0说明 由x个3组成
            if(y==1) return pow(3,x-1)*4;//余数为1 则  拿出一个3和1凑成2*2
            return pow(3,x)*2;      //余数为2直接乘
    }
};

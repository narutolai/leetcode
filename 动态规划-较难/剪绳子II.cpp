给你一根长度为 n 的绳子，请把绳子剪成整数长度的 m 段（m、n都是整数，n>1并且m>1），每段绳子的长度记为 k[0],k[1]...k[m] 。
请问 k[0]*k[1]*...*k[m] 可能的最大乘积是多少？
例如，当绳子的长度是8时，我们把它剪成长度分别为2、3、3的三段，此时得到的最大乘积是18。

答案需要取模 1e9+7（1000000007），如计算初始结果为：1000000008，请返回 1。


示例 1：

输入: 2
输出: 1
解释: 2 = 1 + 1, 1 × 1 = 1
示例 2:

输入: 10
输出: 36
解释: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36


贪心解法
class Solution {
public:
  //快速幂求余
int  remainder(int x, int a, int p)
    {
        int rem = 1;
    while (a > 0)
     {   if (a % 2) rem = (rem * x) % p;
        x = x*x % p;
        a /=2;
     }
    return rem;
    }
    //循环求余
    int remind(int x,int a,int p)
    {
        int res=1;
        for(int i=1;i<=a;i++)
        res=(res*x)%p;
        return res;
    }
    int cuttingRope(int n) {
            int mod=1e9+7;
            if(n<=3) return n-1;
            long res=1;
            while(n>4)
            {
              res*=3;                
              res%=mod;
              n-=3;
            }
            //最后退出循环时n可能等于 1 2 3 4 直接乘就行了
            return (n*res)%mod;
    }
};

写一个函数，输入 n ，求斐波那契（Fibonacci）数列的第 n 项。斐波那契数列的定义如下：

F(0) = 0,   F(1) = 1
F(N) = F(N - 1) + F(N - 2), 其中 N > 1.
斐波那契数列由 0 和 1 开始，之后的斐波那契数就是由之前的两数相加而得出。

答案需要取模 1e9+7（1000000007），如计算初始结果为：1000000008，请返回 1。

 

class Solution {
public:
    int mode=1e9+7;
    //递归超时  你省省吧兄弟
    //动态规划吧
    //0 1 2
    //0 1 1 2 3
    int fib(int n) {
        if(n==0)return 0;
        if(n==1) return 1;
      long long pre=0,cur=1;
      for(int i=2;i<=n;i++)
      {
          long long temp=cur%mode+pre%mode;
          pre=cur;
          cur=temp;
      }
      return cur%mode;
    }
};

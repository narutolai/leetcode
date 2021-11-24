class Solution
{
public:
//好像可以 使用n&(n-1)的方法
  int hammingWeight(uint32_t n)
  {
    //输入一个二进制串？
    int co = 0;
    while (n)
    {
      if (n % 2) //n为奇数
        co++;
      n /= 2;
    }
    return co;
  }
};

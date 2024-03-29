class Solution
{
public:
//好像可以 使用n&(n-1)的方法
//这个是直接输一个二进制串 但也可以用动态规划了
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
//2022/09/25 21:56 这个想法很好.
//其实除以2就是比特位右移,右移的话自然是最低位为1的时候(也就是为奇数时)就会出现一个1呀,
//所以判断一个数是不是奇数的方法就是对2取余数,
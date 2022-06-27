class Solution
{
public:
    int trailingZeroes(int n)
    {
        int count = 0;
        while (n > 0)
        {
            count += n / 5;
            n = n / 5;
        }
        return count;
    }
};
class Solution
{
public:
    int trailingZeroes(int n)
    {
        return n < 5 ? 0 : (n / 5 + trailingZeroes(n / 5));
    }
}
//就是计算从1 - n  这些数 一共有多少个因子5
//遍历次数 1
//1*2*3*4*5*....2*5...3*5...4*5...5*5
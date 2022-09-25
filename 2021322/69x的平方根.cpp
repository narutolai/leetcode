class Solution
{
public:
    int mySqrt(int x)
    {
        int l = 0, r = x, ans = -1;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if ((long long)mid * mid <= x)//O(log(n)).//确实快
            {
                ans = mid;
                l = mid + 1;
            }
            else
            {
                r = mid - 1;
            }
        }
        return ans;
    }
};//这他么都可以二分????
//由下面的for循环可知 我们实际上是在 i---x的平方根之间找一个数
//保证这个数一定可以取平方根对吧
class Solution
{
public:
    int mySqrt(int x)
    {
        long long y = x;
        long long i = 1;
        for (; i * i <= y; i++)//O(n)
            ;

        return i * i == y ? i : i - 1;
    }
};

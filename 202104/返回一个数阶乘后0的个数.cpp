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
//2022-10-03 16:27
//记不住啊
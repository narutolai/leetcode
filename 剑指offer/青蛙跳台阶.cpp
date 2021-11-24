//青蛙可以一次跳一次或一次跳两次
class Solution
{
public:
    int numWays(int n)
    {
        int pre = 1, cur = 1;
        if (n == 0 || n == 1)
            return 1;
        int mode = 1e9 + 7;
        
        for (int i = 2; i <= n; i++)
        {
            int temp = pre % mode + cur % mode;
            pre = cur;
            cur = temp;
        }
        return cur % mode;
    }
};

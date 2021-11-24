class Solution
{
public:
    bool isMonotonic(vector<int> &A)
    {
        int up = 0, down = 0;
        for (int i(0); i < A.size() - 1; i++)
        {
            if (A[i] < A[i + 1])
            {
                up = 1;
                if (down)
                {
                    return false;
                }
            }
            else if (A[i] > A[i + 1])
            {
                down = 1;
                if (up)
                {
                    return false;
                }
            }
            else
            {
                continue;
            }
        }
        return true;
    }
};
//一次遍历 还可以提前退出

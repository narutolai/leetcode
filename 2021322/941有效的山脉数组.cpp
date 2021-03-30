给的一个数组 要求  整个数组是山脉状，不能有相等的， 要求有且只有一个驼峰。

class Solution
{
public:
    bool validMountainArray(vector<int> &arr)
    {
        bool find = false;
        if (arr.size() < 3)
            return false;
        bool up = 0;
        bool down = 0;
        for (int i = 0; i < arr.size() - 1; i++)
        {
            if (arr[i] < arr[i + 1])
            {
                up = 1;
            }
            else if (arr[i] == arr[i + 1])
            {
                return false;
            }
            else
            {
                for (int j = i; j < arr.size() - 1; j++)
                {
                    if (arr[j] > arr[j + 1])
                    {
                        down = 1;
                    }
                    else if (arr[j] == arr[j + 1])
                        return false;
                    else
                    {
                        return false;
                    }
                }
                break;
            }
        }
        return up && down;
    }
};
//这个和上面花的时间和复杂度都是一样的。
class Solution
{
public:
    bool validMountainArray(vector<int> &arr)
    {
        if (arr.size() < 3)
            return false;
        int i = 0, j = arr.size() - 1;
        while (i < arr.size() - 1 && arr[i] < arr[i + 1])
            i++;
        if (i == j)
            return false;
        while (j >= 1 && arr[j - 1] > arr[j])
            j--;
        return i == j && i != 0;
    }
}

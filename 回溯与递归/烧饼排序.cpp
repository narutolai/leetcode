//就是翻烧饼 翻成有序的样子 反转前k个元素 返回一个k序列
//得到的结果不是最优解  即不是最小反转次数。

class Solution
{
public:
    vector<int> res;
    vector<int> pancake(vector<int> &nums)
    {
        sort(nums, nums.size() - 1);
        return res;
    }
    void sort(vector<int> &nums, int index)
    {
        if (index == 0)
            return;
        int maxindex = 0;
        int maxcake = 0;
        for (int i = 0; i <= index; i++)
        {
            if (nums[i] > maxcake)
            {
                maxcake = nums[i];
                maxindex = i;
            }
        }

        //注意这两者的顺序 如果最大的煎饼是第一块 是不需要翻转的
        if (maxindex != 0)
        {
            reverse(nums, 0, maxindex);
            res.push_back(maxindex + 1);
        }

        reverse(nums, 0, index);
        res.push_back(index + 1);

        sort(nums, index - 1);
    }
    void reverse(vector<int> &nums, int left, int right)
    {
        while (left < right)
        {
            swap(nums[left], nums[right]);
            left++;
            right--;
        }
    }
};

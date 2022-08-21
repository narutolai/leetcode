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

        //注意这两者的顺序 如果最大的煎饼是第一块 是不需要翻转的 哈哈哈哈
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
//烧饼排序你知道是干啥不,就是通过不断的翻滚烧饼来排序
//方法是 先找到最大的烧饼， 然后把这个烧饼反转到第一位，然后把所有的烧饼反转，
//这样 这个最大的烧饼就到了最底部，
//遍历次数 2 感觉还行吧!!!!
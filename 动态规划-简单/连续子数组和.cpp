// 给定一个包含非负数的数组和一个目标整数 k，编写一个函数来判断该数组是否含有连续的子数组，
// 其大小至少为 2，总和为 k 的倍数，即总和为 n*k，其中 n 也是一个整数。

// 示例 1:

// 输入: [23,2,4,6,7], k = 6
// 输出: True
// 解释: [2,4] 是一个大小为 2 的子数组，并且和为 6。
// 示例 2:

// 输入: [23,2,6,4,7], k = 6
// 输出: True
// 解释: [23,2,6,4,7]是大小为 5 的子数组，并且和为 42。

//累加余数 对应下标 哈希表 两数之和

class Solution
{
public:
    bool checkSubarraySum(vector<int> &nums, int k)
    {   //<累积 余数,下标>
        unordered_map<int, int> map_;
        //初始时刻，余数为0的时候，把其坐标-1也存进去，其实就是0的左边
        map_[0] = -1;
        int sum = 0;
        //i位置处的余数，不过是余数对应i下标
        for (int i = 0; i < nums.size(); i++)
        {
            sum += nums[i];
            if (k != 0)
                sum = sum % k; //取余数
            if (map_.count(sum))
            {
                if (i - map_[sum] > 1)
                    return true; //因为题目说了长度至少为2
            }
            else
                map_[sum] = i;
        }
        return false;
    }
};
//遍历次数+2
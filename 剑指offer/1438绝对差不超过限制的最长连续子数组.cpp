// 给你一个整数数组 nums ，和一个表示限制的整数 limit，请你返回最长连续子数组的长度，
// 该子数组中的任意两个元素之间的绝对差必须小于或者等于 limit 。
// 如果不存在满足条件的子数组，则返回 0 。
// 示例 1：

// 输入：nums = [8,2,4,7], limit = 4
// 输出：2
// 解释：所有子数组如下：
// [8] 最大绝对差 |8-8| = 0 <= 4.
// [8,2] 最大绝对差 |8-2| = 6 > 4.
// [8,2,4] 最大绝对差 |8-2| = 6 > 4.
// [8,2,4,7] 最大绝对差 |8-2| = 6 > 4.
// [2] 最大绝对差 |2-2| = 0 <= 4.
// [2,4] 最大绝对差 |2-4| = 2 <= 4.
// [2,4,7] 最大绝对差 |2-7| = 5 > 4.
// [4] 最大绝对差 |4-4| = 0 <= 4.
// [4,7] 最大绝对差 |4-7| = 3 <= 4.
// [7] 最大绝对差 |7-7| = 0 <= 4.
// 因此，满足题意的最长子数组的长度为 2 。
// 示例 2：

// 输入：nums = [10,1,2,4,7,2], limit = 5
// 输出：4
// 解释：满足题意的最长子数组是 [2,4,7,2]，其最大绝对差 |2-7| = 5 <= 5 。
// 示例 3：

// 输入：nums = [4,2,2,2,4,4,2,2], limit = 0
// 输出：3
//只要最大值和最小值之差小于limit 那任何元素也都满足了
//使用红黑树 未超时
class Solution
{
public:
    int longestSubarray(vector<int> &nums, int limit)
    {
        //有很多连续子数组，差必须小于等于limit, 找最长的
        int max_num = 0;
        int min_num = 0;
        int result = 0;

        vector<int>::iterator left = nums.begin();
        vector<int>::iterator right;

        multiset<int> s;
        //红黑树就是一颗二叉平衡树
        for (right = nums.begin(); right != nums.end(); right++)
        {
            //向红黑树中插入一个数
            s.insert(*right);
            //关键是不知道二叉树的begin()的迭代器啊。
            max_num = *s.rbegin(); //当前窗口内的最大值和当前窗口内的最小值
            min_num = *s.begin();
            //如果当前窗口内的最大和最小之差小于
            if (max_num - min_num <= limit)
            {
                result = max(result, int(right - left) + 1); //注意两个迭代器相减是其类型为difference_type的带符号整型数。
            }
            else
            {   //从红黑树中删除左边那个数 erase() find() 这波操作。
                s.erase(s.find(*left));
                left++;
            }
        }
        return result;
    }
};

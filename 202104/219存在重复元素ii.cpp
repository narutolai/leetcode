// 给定一个整数数组和一个整数 k，判断数组中是否存在两个不同的索引 i 和 j，使得 nums [i] = nums [j]
// 并且 i 和 j 的差的 绝对值 至多为 k。
 
    // 示例 1:

    // 输入: nums = [1,2,3,1], k = 3
    // 输出: true
    // 示例 2:

    // 输入: nums = [1,0,1,1], k = 1
    // 输出: true
    // 示例 3:

    // 输入: nums = [1,2,3,1,2,3], k = 2
    // 输出: false

class Solution
{
public://总结就是 值相等 但是索引差 <= k  使用map<int,list<int>>  inl;  
    bool containsNearbyDuplicate(vector<int> &nums, int k)
    {
        map<int, list<int>> inl;
        for (int i = 0; i < nums.size(); i++)
        {
            list<int>::iterator itel = inl[nums[i]].begin();
            for (; itel != inl[nums[i]].end(); itel++)
            {
                if (abs(i - *itel) <= k)
                    return true;
            }
            inl[nums[i]].push_front(i);
        }
        return false;
    }
};

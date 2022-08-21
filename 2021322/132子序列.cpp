// 给你一个整数数组 nums ，数组中共有 n 个整数。132 模式的子序列 由三个整数 nums[i]、nums[j] 和 nums[k] 组成，并同时满足：i < j < k 和 nums[i] < nums[k] < nums[j] 。

// 如果 nums 中存在 132 模式的子序列 ，返回 true ；否则，返回 false 。

//  

// 进阶：很容易想到时间复杂度为 O(n^2) 的解决方案，你可以设计一个时间复杂度为 O(n logn) 或 O(n) 的解决方案吗？

//  

// 示例 1：

// 输入：nums = [1,2,3,4]
// 输出：false
// 解释：序列中不存在 132 模式的子序列。
// 示例 2：

// 输入：nums = [3,1,4,2]
// 输出：true
// 解释：序列中有 1 个 132 模式的子序列： [1, 4, 2]
// 关键词   单调栈的建立 while循环pop()的功效

class Solution
{
public:
    bool find132pattern(vector<int> &nums)
    {
        int two = INT_MIN;
        // 保存3的单调栈，从底到顶递减
        stack<int> s;
        int n = nums.size();
        for (int i = n - 1; i >= 0; --i)
        {
            // 找到比2小的数字，那么满足条件
            if (nums[i] >= two)
            {
                // 如果发现大于栈顶(破坏了单调性),那么要去更新栈和two的数值(two变为更大的数字)
                while (!s.empty() && nums[s.top()] < nums[i])
                {
                    two = nums[s.top()];
                    s.pop();
                }
                s.push(i);
            }
            else
            {
                return true;
            }
        }
        return false;
    }
};
//遍历次数 1
/**\      
 *  | 
 *  |          *
 *  |       *     *
 *  |    *
 *  |----------------------->x
*/
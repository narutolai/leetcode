// I 不带重复数字
// 整数数组 nums 按升序排列，数组中的值 互不相同 。

// 在传递给函数之前，nums 在预先未知的某个下标 k（0 <= k < nums.length）上进行了 旋转，
//使数组变为 [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]]（下标 从 0 开始 计数）。
//例如， [0,1,2,4,5,6,7] 在下标 3 处经旋转后可能变为 [4,5,6,7,0,1,2] 。

// 给你 旋转后 的数组 nums 和一个整数 target ，如果 nums 中存在这个目标值 target ，则返回它的下标，否则返回 -1 。

// 要明确的一点是 将有序数组旋转后，肯定会有 [0-mid] 有序或者 [mid-n]有序
// 示例 1：

// 输入：nums = [4,5,6,7,0,1,2], target = 0
// 输出：4
// 示例 2：

// 输入：nums = [4,5,6,7,0,1,2], target = 3
// 输出：-1
// 示例 3：

// 输入：nums = [1], target = 0
// 输出：-1
#include <vector>
#include <iostream>
using namespace std;
class Solution
{
public:
    int search(vector<int> &nums, int target)
    {
        int left = 0, right = nums.size() - 1;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target)
            {
                return mid;
            }
            //带重复数字
            if (nums[left] == nums[mid] && nums[mid] == nums[right])
            {
                ++left;
                --right;
            }
            if (nums[left] <= nums[mid])//那么我可以保证 left---mid 这部分数据是有序的,既然是有序的,那就可以在这之间二分查找数据
            {
                if (nums[left] <= target && target < nums[mid])//如果target在其中 缩小right
                {
                    right = mid - 1;
                }
                else
                {
                    left = mid + 1;                 //否则增大left
                }
            }
            else// nums[mid] <= nums[right]
            {
                if (nums[mid] < target && target <= nums[right])
                {
                    left = mid + 1;
                }
                else
                {
                    right = mid - 1;
                }
            }
        }
        return -1;
    }
};
//这个方法亲测可用 没什么问题的
//遍历次数 1 
//题目应该是旋转数组中找目标数
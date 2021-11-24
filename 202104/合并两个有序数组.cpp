// 给你两个有序整数数组 nums1 和 nums2，请你将 nums2 合并到 nums1 中，使 nums1 成为一个有序数组。

// 初始化 nums1 和 nums2 的元素数量分别为 m 和 n 。你可以假设 nums1 的空间大小等于 m + n，这样它就有足够的空间保存来自 nums2 的元素。

//  

// 示例 1：

// 输入：nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
// 输出：[1,2,2,3,5,6]
// 示例 2：

// 输入：nums1 = [1], m = 1, nums2 = [], n = 0
// 输出：[1]

class Solution
{
public:
    void merge(vector<int> &nums1, int m, vector<int> &nums2, int n)
    {

        int i = 0, j = 0, k = 0;
        while (i < (m + k) && j < n)
        {
            if (nums1[i] <= nums2[j])
            {
                i++;
            }
            else
            {
                int a = m + k;
                while (a > i) //就是要把i开始到最后的几个数整体往后移动 backward_copy()相当于是
                {
                    nums1[a] = nums1[a - 1];
                    a--;
                }
                nums1[i] = nums2[j];

                k++;
                i++;
                j++;
            }
        }
        //剩余部分的转移
        while (j < n)
        {
            nums1[i++] = nums2[j++];
        }
    }
};

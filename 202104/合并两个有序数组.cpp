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

        int iIndexOfNums1 = 0; 
        int iIndexOfNums2 = 0;
        int iMergeNum= 0;
        while (iIndexOfNums1 < (m + iMergeNum) && iIndexOfNums2 < n)
        {
            if (nums1[iIndexOfNums1] <= nums2[iIndexOfNums2])
            {
                iIndexOfNums1++;
            }
            else
            {
                int iSizeOfNums1 = m + iMergeNum;
                while (iSizeOfNums1 > iIndexOfNums1) //就是要把i开始到最后的几个数整体往后移动 backward_copy()相当于是
                {
                    nums1[iSizeOfNums1] = nums1[iSizeOfNums1 - 1];
                    iSizeOfNums1--;
                }
                //把数往后挪然后给这个数让个位置
                nums1[iIndexOfNums1] = nums2[iIndexOfNums2];

                iMergeNum++;
                iIndexOfNums1++;
                iIndexOfNums2++;
            }
        }
        //剩余部分的转移
        while (iIndexOfNums2 < n)
        {
            nums1[iIndexOfNums1++] = nums2[iIndexOfNums2++];
        }
    }
};
//尝试命名规范下,这样方便读懂程序的意思。
// 合并多少数量这个遍历很重要的
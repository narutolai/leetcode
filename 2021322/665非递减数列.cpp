给你一个长度为 n 的整数数组，请你判断在 最多 改变 1 个元素的情况下，该数组能否变成一个非递减数列。

我们是这样定义一个非递减数列的： 对于数组中任意的 i (0 <= i <= n-2)，总满足 nums[i] <= nums[i + 1]。

 

示例 1:

输入: nums = [4,2,3]
输出: true
解释: 你可以通过把第一个4变成1来使得它成为一个非递减数列。
示例 2:

输入: nums = [4,2,1]
输出: false
解释: 你不能在只改变一个元素的情况下将其变为非递减数列。

这题目小看了它，就是在 遇见  i>i+1  时 要比较  要根据i+1 和 i-1的大小 来决定是把 i变成i+1 还是 i+1变成i;

3 4 2   因为2大于3 所以 就可以让4降成2 而不是让2升4 ，尽量选择保守的做法可以方便后面的递增。 
2 4 3   因为3大于2 所以没办法，只能3升4了。不然无法满足非递减。
class Solution
{
public:
    bool checkPossibility(vector<int> &nums)
    {
       
        int count = 1;
        for (int i = 0; i < nums.size()-1; i++)
        {
           if(nums[i]>nums[i+1])
           {
                if(i==0||nums[i+1]>=nums[i-1])
                {
                        nums[i]=nums[i+1];
                }
                else{
                    nums[i+1]=nums[i];
                }
                if(count==0)
                return false;
                count--;
           }
        }
        return true;
    }
};

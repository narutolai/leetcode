80. 删除有序数组中的重复项 II
给你一个有序数组 nums ，请你 原地 删除重复出现的元素，使每个元素 最多出现两次 ，返回删除后数组的新长度。

不要使用额外的数组空间，你必须在 原地 修改输入数组 并在使用 O(1) 额外空间的条件下完成。

 每一个元素最多返回两次 
 class Solution
{
public: //之前做过删除链表中的
    int removeDuplicates(vector<int> &nums)
    {
        stack<int> stk;
        bool gettwo = false;
        stk.push(nums[0]);
        for (int i = 1; i < nums.size(); i++)
        {
            if (nums[i] != stk.top())
            {
                gettwo=false;
                stk.push(nums[i]);
            }
            else if(nums[i]==stk.top())
            {
                if(gettwo)
                {
                    continue;
                }
                else
                {
                   stk.push(nums[i]);
                   gettwo=true; 
                }
            }
        }
        return stk.size();
    }
};
//真的是蠢哦 我想了一个上午 我去你大爷的
class Solution
{
public: 
    int removeDuplicates(vector<int> &nums)
    {
        if (nums.size() < 2)
            return nums.size();
        int j = 2;

        for (int i = 2; i < nums.size(); i++)
        {
            if (nums[j - 2] != nums[i])
            {
                nums[j++] = nums[i];
            }
        }
        return j;
    }
};

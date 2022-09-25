// 80. 删除有序数组中的重复项 II
// 给你一个有序数组 nums ，请你 原地 删除重复出现的元素，使每个元素 最多出现两次 ，返回删除后数组的新长度。

// 不要使用额外的数组空间，你必须在 原地 修改输入数组 并在使用 O(1) 额外空间的条件下完成。

//  每一个元素最多返回两次 

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
//想想下最极端的情况,所有的元素都是相同的 都是1
//假设你可以使用另一个数组 你会怎么做呢
//删除重复的元素,每一个元素最多出现2次,那么就可以使用另外一个数组 ，然后把头两个元素拷贝过来，从第三个元素开始计算。
/**
 *            i
 *  1    1    1    1    1   原数组
 *      
 *  1    1    0    0    0   开辟一个新数组
 *  
 *  j-2 j-1   j
*  /
//遍历次数: 3
给你一个整数数组 nums ，和一个表示限制的整数 limit，请你返回最长连续子数组的长度，该子数组中的任意两个元素之间的绝对差必须小于或者等于 limit 。

如果不存在满足条件的子数组，则返回 0 。

 

示例 1：

输入：nums = [8,2,4,7], limit = 4
输出：2 
解释：所有子数组如下：
[8] 最大绝对差 |8-8| = 0 <= 4.
[8,2] 最大绝对差 |8-2| = 6 > 4. 
[8,2,4] 最大绝对差 |8-2| = 6 > 4.
[8,2,4,7] 最大绝对差 |8-2| = 6 > 4.
[2] 最大绝对差 |2-2| = 0 <= 4.
[2,4] 最大绝对差 |2-4| = 2 <= 4.
[2,4,7] 最大绝对差 |2-7| = 5 > 4.
[4] 最大绝对差 |4-4| = 0 <= 4.
[4,7] 最大绝对差 |4-7| = 3 <= 4.
[7] 最大绝对差 |7-7| = 0 <= 4. 
因此，满足题意的最长子数组的长度为 2 。
示例 2：

输入：nums = [10,1,2,4,7,2], limit = 5
输出：4 
解释：满足题意的最长子数组是 [2,4,7,2]，其最大绝对差 |2-7| = 5 <= 5 。
示例 3：

输入：nums = [4,2,2,2,4,4,2,2], limit = 0
输出：3

超时的办法
class Solution {
public:
    int longestSubarray(vector<int>& nums, int limit) {
    //有很多连续子数组，差必须小于等于limit, 找最长的
  int max_num = 0;
    int min_num = 0;
    int result=0;

    vector<int>::iterator left ;
    vector<int>::iterator right;
    for(right=nums.begin();right!=nums.end();right++)
    for (left=nums.begin(); left !=right+1; left++)
    {
        //返回当前 序列中最大元素值
        max_num = *max_element(left, right+1);//注意返回的是迭代器
        min_num=  *min_element(left,right+1); //注意要加 1
      
        //如果小于等于规定值
        if(max_num-min_num<=limit)
        {
            result=max(result,int(right-left)+1);//注意两个迭代器相减是其类型为difference_type的带符号整型数。
        }
    }
    return result;
    }
};
//使用滑动窗口还是超时
class Solution {
public:
    int longestSubarray(vector<int>& nums, int limit) {
    //有很多连续子数组，差必须小于等于limit, 找最长的
    int max_num = 0;
    int min_num = 0;
    int result=0;

    vector<int>::iterator left=nums.begin() ;
    vector<int>::iterator right;
   
    for (right = nums.begin(); right != nums.end(); right++)
    {

        max_num = *max_element(left, right + 1); //注意返回的是迭代器
        min_num = *min_element(left, right + 1); //注意这里要加1
        //如果当前窗口内的最大和最小之差小于
        if (max_num - min_num <= limit)
        {
            result = max(result, int(right - left) + 1); //注意两个迭代器相减是其类型为difference_type的带符号整型数。
        }
        else
        {
            left++;
        }
    }
    return result;
    }
};





//使用红黑树 未超时
class Solution {
public:
    int longestSubarray(vector<int>& nums, int limit) {
    //有很多连续子数组，差必须小于等于limit, 找最长的
    int max_num = 0;
    int min_num = 0;
    int result=0;

    vector<int>::iterator left=nums.begin() ;
    vector<int>::iterator right;
     
    multiset<int> s;

    for (right = nums.begin(); right != nums.end();right++)
    {
        s.insert(*right);
        max_num = *s.rbegin(); //当前树的最大值，
        min_num = *s.begin();
        //如果当前窗口内的最大和最小之差小于
        if (max_num - min_num <= limit)
        {
            result = max(result, int(right - left) + 1); //注意两个迭代器相减是其类型为difference_type的带符号整型数。
        }
        else
        {   //从红黑树中删除左边那颗
            s.erase(s.find(*left));
            left++;
        }
    }
    return result;
    }
};

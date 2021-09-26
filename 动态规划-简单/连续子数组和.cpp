给定一个包含非负数的数组和一个目标整数 k，编写一个函数来判断该数组是否含有连续的子数组，其大小至少为 2，总和为 k 的倍数，即总和为 n*k，其中 n 也是一个整数。

示例 1:

输入: [23,2,4,6,7], k = 6
输出: True
解释: [2,4] 是一个大小为 2 的子数组，并且和为 6。
示例 2:

输入: [23,2,6,4,7], k = 6
输出: True
解释: [23,2,6,4,7]是大小为 5 的子数组，并且和为 42。

//解法是使用hashmap，索引对应其累加和取余
/*
我们遍历一遍给定的数组，记录到当前位置为止的 sum%ksum 。一旦我们找到新的 sum%ksum 的值（即在 HashMap 中没有这个值），
我们就往 HashMap 中插入一条记录 (sum%k, i)(sum 。
现在，假设第 ii 个位置的 sum%ksum 的值为 remrem 。如果以 ii 为左端点的任何子数组的和是 kk 的倍数，比方说这个位置为 jj ，
那么 HashMap 中第 jj 个元素保存的值为 (rem + n*k)\%k(rem+n∗k)%k ，其中 nn 是某个大于 0 的整数。
我们会发现 (rem + n*k)\%k = rem(rem+n∗k)%k=rem ，也就是跟第 ii 个元素保存到 HashMap 中的值相同。
基于这一观察，我们得出结论：无论何时，只要 sum%ksum 的值已经被放入 HashMap 中了，代表着有两个索引 ii 和 jj ，它们之间元素的和是 kk 的整数倍。因此，只要 HashMap 中有相同的 sum\%ksum%k ，我们就可以直接返回 \teat{True} 。
*/

class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
            unordered_map<int,int> map_;
            //初始时刻，余数为0的时候，把其坐标-1也存进去，其实就是0的左边
            map_[0]=-1;
            int sum=0;
            //i位置处的余数，不过是余数对应i下标
            for(int i=0;i<nums.size();i++)
            {
                sum+=nums[i];
                if(k!=0)
                 sum=sum%k; //取余数
                if(map_.count(sum))
                {
                    if(i-map_[sum]>1) return true;   //因为题目说了长度至少为2
                }
                else map_[sum]=i;
            }
            return false;
    }
};

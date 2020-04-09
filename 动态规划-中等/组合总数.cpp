给定一个由正整数组成且不存在重复数字的数组，找出和为给定目标正整数的组合的个数可重复使用

示例:

nums = [1, 2, 3]
target = 4

所有可能的组合为：
(1, 1, 1, 1)
(1, 1, 2)
(1, 2, 1)
(1, 3)
(2, 1, 1)
(2, 2)
(3, 1)

请注意，顺序不同的序列被视作不同的组合。

因此输出为 7。
class Solution{
public:
    int combinationSum4(vector<int>&nums,int target)
    {
        vector<unsigned long long> memo(target+1,0);
        memo[0]=1; 
        for(int i=0;i<target;i++)   
            for(int num:nums)      //  i  num
            if(i+num<=target)      //4=1 + 3
            memo[i+num]+=memo[i];  //4=2 + 2

        return memo[target];
    }
};

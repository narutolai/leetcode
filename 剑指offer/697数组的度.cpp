class Solution {
public:
    int findShortestSubArray(vector<int>& nums) {
    
//第一个存 出现次数，然后是起始位置， 结束位置 
    vector<int> dp = {0, -1, -1};
    map<int, vector<int>> count;
    int target = INT_MIN;

//通过这个for循环可以将每一个元素的这些信息填充并且找出数组的度
    for (int i = 0; i < nums.size(); i++)
    {
        if(count[nums[i]].size()==0)
            count[nums[i]] = dp;

        count[nums[i]][0] += 1;
      //起始位置只要记录一次
        if (count[nums[i]][1] == -1)
        {
            count[nums[i]][1] = i;
        }
//结束位置，记录到最后一次
        count[nums[i]][2] = i;

        target = target < count[nums[i]][0] ? count[nums[i]][0] : target;
    }

    map<int, vector<int>>::iterator iter;

    int shortest = INT_MAX;
//然后遍历这个map找出最大度里最短的子数组
    for (iter = count.begin(); iter != count.end(); iter++)
        if (iter->second[0] == target) 
        {
            shortest = shortest > iter->second[2] - iter->second[1] ? iter->second[2] - iter->second[1] : shortest;
        }
    return shortest+1;
    }
};

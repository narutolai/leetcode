#if 0
给定一些区间 然后合并所有的区间 两个区间有交集就合并
输入:[[1,3],[3,6],[8,10],[15,18]]
输出:[[1,6],[8,10],[15,18]]

解释 [1,3]和[3,6]区间合并了.
#endif
#include <vector>
#include <algorithm>
using namespace std;
class Solution
{
public:
    vector<vector<int>> MergeInterVal(vector<vector<int>> &intervals)
    {
        vector<vector<int>> result;

        sort(intervals.begin(), intervals.end());
        //先把第一个压入区间
        result.push_back(intervals[0]);
        //遍历剩余的区间
        for (auto &interval : intervals)
        {
            auto &last = result.back();
            if (interval[0] <= last[1])
            {
                last[1] = max(last[1], interval[1]);
            }
            else
            {
                result.push_back(interval);
            }
        }
        return result;
    }
};
//感觉这个做法很ok 不知道可不可以用在别的区间问题上呢
#include<iostream>
// 这个好像按start排序就可以
int main()
{
    Solution so;
    vector<vector<int>> temp = {{1, 3}, {3, 6}, {8, 10}, {15, 18}};
    vector<vector<int>> result = so.MergeInterVal(temp);
    for(auto &item :result)
    {
        cout<<item[0]<<" "<<item[1]<<endl;
    }
    return 0;
}
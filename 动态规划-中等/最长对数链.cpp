给出 n 个数对。 在每一个数对中，第一个数字总是比第二个数字小。

现在，我们定义一种跟随关系，当且仅当 b < c 时，数对(c, d) 才可以跟在 (a, b) 后面。我们用这种形式来构造一个数对链。

给定一个对数集合，找出能够形成的最长数对链的长度。你不需要用到所有的数对，你可以以任何顺序选择其中的一些数对来构造。

示例 :

输入: [[1,2], [2,3], [3,4]]
输出: 2
解释: 最长的数对链是 [1,2] -> [3,4]
注意：

给出数对的个数在 [1, 1000] 范围内。


class Solution {
public:   //区间问题
        //贪心问题
    int findLongestChain(vector<vector<int>>& pairs)
    {
    //先按照结束时间排序
        sort(pairs.begin(), pairs.end(), [&](const vector<int> &A, const vector<int> &B) {
            return A[1] < B[1];
        });

        int res=1;
        int maxend=pairs[0][1];

        for(int i=1;i<pairs.size();i++)
        {
            auto &cur=pairs[i];//如果当前区间的起始大于上一个的结束 
            if(cur[0]>maxend)
            {   res++;
                maxend=cur[1];
            }
        }
    return res;
    } 
};


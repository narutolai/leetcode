返回 A 的最短的非空连续子数组的长度，该子数组的和至少为 K 。

如果没有和至少为 K 的非空子数组，返回 -1 。

 

示例 1：

输入：A = [1], K = 1
输出：1
示例 2：

输入：A = [1,2], K = 4
输出：-1
示例 3：

输入：A = [2,-1,2], K = 3
输出：3

//使用队列解答题目
class Solution {
public:

    int shortestSubarray(vector<int> &A, int K)
    {
        A.insert(A.begin(), 0);

        vector<int> presum = vector<int>(A.size(), 0);
        deque<int> buff;
        int minvalue = INT32_MAX;

        for (int i = 0; i < presum.size(); i++) {
            if (i == 0) {
                presum[i] = A[i];
            } else {
                presum[i] = presum[i - 1] + A[i];
            }
        }

        for (int i = 0; i < presum.size(); i++) {
            
            while(!buff.empty() && presum[i]<presum[buff.front()]){
                buff.pop_front();
            }

            while(!buff.empty() && presum[i] - presum[buff.back()]>=K){
                minvalue = min(minvalue,i-buff.back());
                buff.pop_back();
            }

            buff.push_front(i);

        }

        return minvalue == INT32_MAX ? -1 : minvalue;
    }
};

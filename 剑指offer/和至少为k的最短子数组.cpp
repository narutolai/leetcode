// 返回 A 的最短的非空连续子数组的长度，该子数组的和至少为 K 。

// 如果没有和至少为 K 的非空子数组，返回 -1 。

// 示例 1：

// 输入：A = [1], K = 1
// 输出：1
// 示例 2：

// 输入：A = [1,2], K = 4
// 输出：-1
// 示例 3：

// 输入：A = [2,-1,2], K = 3
// 输出：3

//使用队列解答题目
class Solution
{
public:
    int shortestSubarray(vector<int> &A, int K)
    {
        vector<int> presum(A.size(), 0);
        deque<int> buff;
        int minvalue = INT32_MAX;

        //为什么还有一个前缀和
        for (int i = 0; i < presum.size(); i++)
        {
            presum[i] = (i - 1 < 0 ? 0 : presum[i - 1]) + A[i];
        }
        //存储下标
        //想象成是一个窗口
        for (int i = 0; i < presum.size(); i++)
        {   
            //保持deque中的前缀和是递增的
            while (!buff.empty() && presum[i] < presum[buff.front()]) //就是说A[i]是个负数
            {
                buff.pop_front(); //弹出到抵消的那一刻
            }
            //换句话说 buff里存的前缀和下标都是递增的 为什么去掉负数  因为负数的存在肯定会使得子数组最长。
 
            //只要和大于K 就一直弹pop_back()
            while (!buff.empty() && presum[i] - presum[buff.back()] >= K) //1 2 3 4 5 -5
            {
                minvalue = min(minvalue, i - buff.back());
                buff.pop_back();
            }
            buff.push_front(i);
        }
        return minvalue == INT32_MAX ? -1 : minvalue;
    }
};
//deque buff
//      pop_back() <------|||||||||||---->pop_front()
//遍历次数 1 至今不明白 有没有别的解法
//这样总是可以获取最小值吗
//假如数据是 2 2 2 2 -4
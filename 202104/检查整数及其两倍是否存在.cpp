// 给你一个整数数组 arr，请你检查是否存在两个整数 N 和 M，满足 N 是 M 的两倍（即，N = 2 * M）。

// 更正式地，检查是否存在两个下标 i 和 j 满足：

// i != j
// 0 <= i, j < arr.length
// arr[i] == 2 * arr[j]
//  

// 示例 1：

// 输入：arr = [10,2,5,3]
// 输出：true
// 解释：N = 10 是 M = 5 的两倍，即 10 = 2 * 5 。
// 示例 2：

// 输入：arr = [7,1,14,11]
// 输出：true
// 解释：N = 14 是 M = 7 的两倍，即 14 = 2 * 7 。
// 示例 3：

// 输入：arr = [3,1,7,11]
// 输出：false
// 解释：在该情况下不存在 N 和 M 满足 N = 2 * M 。

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/check-if-n-and-its-double-exist
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

class Solution
{
public:
    bool checkIfExist(vector<int> &arr)
    {

        unordered_map<int, int> m;
        for (auto &x : arr)
        {   // 如果一个数的2倍存在或者一个数的一半存在且x不为0 那么就return true;
            if (m[x * 2] || m[x / 2] && x % 2 == 0)//相乘 或 相除且余数为0.
                return true;    //return true;
            else
                m[x] = 1;
        }
        return false;
    }
};

//遍历次数 1
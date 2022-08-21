// 给你一个整数数组，返回它的某个 非空 子数组（连续元素）在执行一次可选的删除操作后，所能得到的最大元素总和。

// 换句话说，你可以从原数组中选出一个子数组，并可以决定要不要从中删除一个元素（只能删一次哦），（删除后）子数组中至少应当有一个元素，

// 然后该子数组（剩下）的元素总和是所有子数组之中最大的。

// 注意，删除一个元素后，子数组 不能为空。

// 请看示例：

// 示例 1：

// 输入：arr = [1,-2,0,3]
// 输出：4
// 解释：我们可以选出 [1, -2, 0, 3]，然后删掉 -2，这样得到 [1, 0, 3]，和最大。
// 示例 2：

// 输入：arr = [1,-2,-2,3]
// 输出：3
// 解释：我们直接选出 [3]，这就是最大和。
// 示例 3：

// 输入：arr = [-1,-1,-1,-1]
// 输出：-1
// 解释：最后得到的子数组不能为空，所以我们不能选择 [-1] 并从中删去 -1 来得到 0。
//      我们应该直接选择 [-1]，或者选择 [-1, -1] 再从中删去一个 -1。

class Solution
{
public:
    int maximumSum(vector<int> &arr)
    {
        int n = arr.size();
        int ans = 0;
        vector<int> left(n, 0);
        vector<int> right(n, 0);

        /*intial*/
        left[0] = arr[0];
        right[n - 1] = arr[n - 1];
        /*left*/
        ans = max(left[0], right[n - 1]);
        for (int i = 1; i < n; ++i)
        {
            left[i] = arr[i] + max(0, left[i - 1]);
            ans = max(ans, left[i]);
        }
        /*right*/
        for (int i = n - 2; i >= 0; --i)
        {
            right[i] = arr[i] + max(0, right[i + 1]);
            ans = max(ans, right[i]);
        }
        for (int i = 1; i <= n - 2; ++i)
        {
            ans = max(left[i - 1] + right[i + 1], ans);
        }
        return ans;
    }
};

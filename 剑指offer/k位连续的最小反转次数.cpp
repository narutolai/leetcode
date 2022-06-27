// 在仅包含 0 和 1 的数组 A 中，一次 K 位翻转包括选择一个长度为 K 的（连续）子数组，同时将子数组中的每个 0 更改为 1，而每个 1 更改为 0。

// 返回所需的 K 位翻转的最小次数，以便数组没有值为 0 的元素。如果不可能，返回 -1。

//  

// 示例 1：

// 输入：A = [0,1,0], K = 1
// 输出：2
// 解释：先翻转 A[0]，然后翻转 A[2]。
// 示例 2：

// 输入：A = [1,1,0], K = 2
// 输出：-1
// 解释：无论我们怎样翻转大小为 2 的子数组，我们都不能使数组变为 [1,1,1]。
// 示例 3：

// 输入：A = [0,0,0,1,0,1,1,0], K = 3
// 输出：3
// 解释：
// 翻转 A[0],A[1],A[2]: A变成 [1,1,1,1,0,1,1,0]
// 翻转 A[4],A[5],A[6]: A变成 [1,1,1,1,1,0,0,0]
// 翻转 A[5],A[6],A[7]: A变成 [1,1,1,1,1,1,1,1]
// 方法1暴力解法是从左往右遍历 遇见0就开始翻转后面的k个数 时间复杂度是n平方。
// 方法 2 滑动窗口解法  
// 方法三 差分数组的解法 我直接差分数组 Revertdiff[i] = revert[i] - revert[i-1];//revert是代表每一个位置的翻转次数
/** d[0] = r[0]
 *  d[1] = r[1] - r[0]
 *  d[2] = r[2] - r[1]
 *  d[3] = r[3] - r[2]
 * 左边相加 右边相加
 * d[0]+d[1]+d[2]+...d[i] = r[i];//由差分数组  求原数组
*/
class Solution
{
public:
    int minKBitFlips(vector<int> &A, int K)
    {
        //
        int n = A.size();
        vector<int> diff(n + 1);
        int ans = 0, revCnt = 0;
        for (int i = 0; i < n; ++i)
        {
            revCnt += diff[i]; //所以这里直接累加 revCnt就是当前数的翻转次数
            //为什么当前数加上其已经反转次数未偶数 就要反转Z？
            //A[i] 1 就要 翻转次数1 为偶数  如果A[i]为奇数 那么翻转次数就是奇数，
            //A[i]是0 如果A[i] 是0 那么翻转次数为偶数 才可以为
            //那不就是当前数为0吗
            if ((A[i] + revCnt) % 2 == 0)
            {//目的是把 0翻转1啊
                if (i + K > n)
                {
                    return -1;
                }
                ++ans;
                ++revCnt;
                --diff[i + K];
            }
        }
        return ans;
    }
};
//遍历次数 1
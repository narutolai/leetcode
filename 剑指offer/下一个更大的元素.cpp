// 给定一个循环数组（最后一个元素的下一个元素是数组的第一个元素），输出每个元素的下一个更大元素。数字 x 的下一个更大的元素是按数组遍历顺序，
//这个数字之后的第一个比它更大的数，这意味着你应该循环地搜索它的下一个更大的数。如果不存在，则输出 -1。

// 示例 1:

// 输入: [1,2,1]
// 输出: [2,-1,2]
// 解释: 第一个 1 的下一个更大的数是 2；
// 数字 2 找不到下一个更大的数；
// 第二个 1 的下一个最大的数需要循环搜索，结果也是 2。

//暴力解法  其实处理循环数组 下标取余即可！！！
class Solution
{
public:
	vector<int> nextGreaterElements(vector<int> &nums)
	{
		vector<int> result(nums.size(), 0);
		int i = 0, j = 0;

		for (int i = 0; i < result.size(); i++)
		{
			bool flag = false;
			j = (i == result.size() - 1) ? 0 : (i + 1);
			while (nums[j] <= nums[i])
			{
				j = (j == result.size() - 1) ? 0 : j + 1;
				if (i == result.size() - 1 && j == i)
				{
					result[i] = -1;
					flag = true;
					break;
				}
				if (j == i + 1)
				{
					result[i] = -1;
					flag = true;
					break;
				}
			}
			if (!flag)
				result[i] = nums[j];
		}
		return result;
	}
};

// 单调栈解法
// 建立「单调递减栈」，并对原数组遍历一次：

// 如果栈为空，则把当前元素放入栈内；
// 如果栈不为空，则需要判断当前元素和栈顶元素的大小：
// 如果当前元素比栈顶元素大：说明当前元素是前面一些元素的「下一个更大元素」，则逐个弹出栈顶元素，直到当前元素比栈顶元素小为止。
// 如果当前元素比栈顶元素小：说明当前元素的「下一个更大元素」与栈顶元素相同，则把当前元素入栈。

// 我们可以使用单调栈解决本题。单调栈中保存的是下标，从栈底到栈顶的下标在数组 \textit{nums}nums 中对应的值是单调不升的。
// 每次我们移动到数组中的一个新的位置 ii，我们就将当前单调栈中所有对应值小于 \textit{nums}[i]nums[i] 的下标弹出单调栈，这些值的下一个更大元素即为 \textit{nums}[i]nums[i]（证明很简单：如果有更靠前的更大元素，那么这些位置将被提前弹出栈）。随后我们将位置 ii 入栈。
// 但是注意到只遍历一次序列是不够的，例如序列 [2,3,1][2,3,1]，最后单调栈中将剩余 [3,1][3,1]，其中元素 [1][1] 的下一个更大元素还是不知道的。
// 一个朴素的思想是，我们可以把这个循环数组「拉直」，即复制该序列的前 n-1n−1 个元素拼接在原序列的后面。这样我们就可以将这个新序列当作普通序列，用上文的方法来处理。
// 而在本题中，我们不需要显性地将该循环数组「拉直」，而只需要在处理时对下标取模即可
class Solution
{
public:
	vector<int> nextGreaterElements(vector<int> &nums)
	{
		int n = nums.size();
		vector<int> result(nums.size(), -1);
		//单调递减栈 存储下标 不存数
		stack<int> st;
		for (int i = 0; i < 2 * n - 1; i++)
		{
			//如果当前元素大于栈顶下标元素，可以一屁股坐死的都一屁股坐死。
			while (!st.empty() && nums[i % n] > nums[st.top()])
			{
				result[st.top()] = nums[i % n];
				st.pop();
			}
			st.push(i % n);
		}
		return result;
	}
};

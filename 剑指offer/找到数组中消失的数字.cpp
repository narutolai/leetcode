// 给定一个范围在  1 ≤ a[i] ≤ n ( n = 数组大小 ) 的 整型数组，数组中的元素一些出现了两次，另一些只出现一次。

// 找到所有在 [1, n] 范围之间没有出现在数组中的数字。

// 您能在不使用额外空间且时间复杂度为O(n)的情况下完成这个任务吗? 你可以假定返回的数组不算在额外空间内。

// 示例:

// 输入:
// [4,3,2,7,8,2,3,1]

// 输出:
// [5,6]

class Solution
{
public:
    vector<int> findDisappearedNumbers(vector<int> &nums)
    {
        vector<int> res;
        if (nums.empty())
            return nums;

        /**
         * 我们可以这样思考，假设nums是升序的 然后每一个索引上都应该有固定的数 即在index=i处的数是i+1,或者每一个数有固定的位置。
         * 索引值和数是对应有关系的
         * 其实可以 使用一个 map<int,int> num2index
        */
        for (int i = 0; i < nums.size(); i++)
        {
            //如果一个数出现了两次
            nums[(nums[i] - 1) % nums.size()] += nums.size(); //加什么都行 加一个超过最大值的数就行了。
        }

        //不看解
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] <= nums.size())
                res.push_back(i + 1);
        }
        return res;
    }

    //使用map的方法,假设可以使用额外空间。
    vector<int> findDisappearedNumbers(vector<int> &nums)
    {
        vector<int> res;
        if (nums.empty())
            return nums;
        map<int, int> num2index;

        for (int i = 0; i < nums.size(); i++)
        {
            //把索引存一遍
            num2index[i]++;
            //索引上有数也存一遍
            num2index[nums[i] - 1]++;
        }

        for (auto &item : num2index)
        {
            if (item.second < 2)
                cout << item.first + 1 << endl;
        }
        return res;
    }
};

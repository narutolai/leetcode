自己第一个问题是没有重复元素
//没有重复元素
迭代法就是用一个长度为n的0/1序列来代表 是否要抓取该数 比如一个长度为3的数组{3，4，5} 那么子集一共有 000-111 8种情况 所以就是0-2^3-1; 就是 1<<3 往左边移3 就是 1000 就是8  
class Solution {
public:
    vector<int> t;
    vector<vector<int>> ans;
    //与运算是当成二进制来计算的，，
    vector<vector<int>> subsets(vector<int>& nums) {
        int n = nums.size();
        // 1<<n的值就是 二进制  十进制  1往左移动n位
        for (int mask = 0; mask < (1 << n); ++mask) {
            t.clear();
            for (int i = 0; i < n; ++i) {
                if (mask & (1 << i)) {      //mask=0000 0010 时 1 往左移i位 
                    t.push_back(nums[i]);
                }
            }
            ans.push_back(t);
        }
        return ans;
    }
};

mask     1左移i位
001      1左移0位
010      1左移1位
100      1左移2位
101      1左移0位，2位
110      1左移1位，2位 



回溯法  递归树 面对当前树 有选择和不选择两种，这个数的每个叶子节点都要遍历到
class Solution {
public:
    vector<int> t;
    vector<vector<int>> ans;

    void dfs(int cur, vector<int>& nums) {
        if (cur == nums.size()) {
            ans.push_back(t);
            return;
        }
        t.push_back(nums[cur]);//选
        dfs(cur + 1, nums);
        t.pop_back();      //弹出 不选
        dfs(cur + 1, nums);
    }

    vector<vector<int>> subsets(vector<int>& nums) {
        dfs(0, nums);
        return ans;
    }
};

//有重复元素
class Solution {
public:
    vector<int> t;
    vector<vector<int>> ans;

    vector<vector<int>> subsetsWithDup(vector<int> &nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        for (int mask = 0; mask < (1 << n); ++mask) {
            t.clear();
            bool flag = true;
            for (int i = 0; i < n; ++i) {
                if (mask & (1 << i)) {//迭代时，若发现没有选择上一个数，且当前数字与上一个数相同，则可以跳过当前生成的子集。
                    if (i > 0 && (mask >> (i - 1) & 1) == 0 && nums[i] == nums[i - 1]) {
                        flag = false;
                        break;
                    }
                    t.push_back(nums[i]);
                }
            }
            if (flag) {
                ans.push_back(t);
            }
        }
        return ans;
    }
};
           i-1 i 
         1  2  2
mask     i
001      0
010      1
100      2
101      0，2
110      1，2 




递归树
class Solution {
public:
    vector<int> t;
    vector<vector<int>> ans;

    void dfs(bool choosePre, int cur, vector<int> &nums) {
        if (cur == nums.size()) {
            ans.push_back(t);
            return;
        }
        dfs(false, cur + 1, nums);
        if (!choosePre && cur > 0 && nums[cur - 1] == nums[cur]) {
            return;
        }
        t.push_back(nums[cur]);
        dfs(true, cur + 1, nums);
        t.pop_back();
    }

    vector<vector<int>> subsetsWithDup(vector<int> &nums) {
        sort(nums.begin(), nums.end());
        dfs(false, 0, nums);
        return ans;
    }
};
===============================================================================================
//自己的蹩脚解法
class Solution
{
public:
    vector<vector<int>> result;
    vector<vector<int>> Combination(vector<int> &nums, int m, int n)
    {
        vector<vector<int>> cur_index;
        if (n == 1)
        {
            for (int i = 0; i < m; i++)
            {
                result.push_back({nums[i]});
                cur_index.push_back({i});
            }
            return cur_index;
        }
        //前一个的排列组合
        vector<vector<int>> pre_index = Combination(nums, m, n - 1);
        vector<int>::iterator iter;
        for (auto &vec : pre_index)
        {
          for(int i=vec.back()+1;i<m;i++)
          {
                vec.push_back(i);
                cur_index.push_back(vec);
                vector<int> tdl;
                for(auto &in_d:vec)
                    tdl.push_back(nums[in_d]);
                result.push_back(tdl);
                vec.pop_back();
            }
        }
        return cur_index;
    }
    vector<vector<int>> subsetsWithDup(vector<int> &nums)
    {
        //先排个序吧
        sort(nums.begin(), nums.end());
        Combination(nums, nums.size(), nums.size());
        result.push_back({});
        sort(result.begin(),result.end());
        result.erase(unique(result.begin(), result.end()), result.end());
        return result;
    }
};

// 组合算法
// 比如 6个元素里选4个 有几种选法。
// 1 2 3 4 
// 1 2 3 5
// 1 2 3 6
// //组合算法
// //竟然是我自己慢慢思考出来的 假设返回值就是排列组合
vector<vector<int>> Combination(int m, int n)
{
    vector<vector<int>> result;
    if (n == 1)
    {
        for (int i = 1; i <= m; i++)
            result.push_back({i});
        return result;
    }
    //前一个的排列组合
    vector<vector<int>> pre = Combination(m, n - 1);
    for (auto &vec : pre)
        for (int i = vec.back() + 1; i <= m; i++)
        {
            vec.push_back(i);
            result.push_back(vec);
            vec.pop_back();
        }
    return result;
}

// //排列算法
// 2个元素
// 1 2     2 1 
// 3个元素
// 就是把3分别插在2个元素时产生的结果的每一个位置上
// 3 1 2  1 3 2  1 2 3
// 3 2 1  2 3 1  2 1 3 
// 难怪 排列是 3*2  
 
vector<vector<int>> Arrangement(int m)
{
    vector<vector<int>> result;
    if (m == 1)
    {
        result.push_back({1});
        return result;
    }
    vector<vector<int>> pre = Arrangement(m - 1);
    vector<int>::iterator iter;
    for (auto &vec : pre)
    {
        int i = 0;
        while (i != m)
        {     
            iter = vec.insert(vec.begin() + i, m);//迭代器的作用就出现了。。。。分别在不同的位置插入元素m
            result.push_back(vec);
            vec.erase(iter);                    //然后再删除该元素
            i++;
        }
    }
    return result;
}

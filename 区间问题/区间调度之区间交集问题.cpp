#if 0
给定两个区间 列表 返回连个区间列表的交集
A = {{0,2},{5,10},{13,23},{24,25}}
B ={{1,2},{5,5},{8,10},{15,23},{24,24},{25,25}}

输出 区间的交集
#endif

class Solution
{
public:
    vector<vector<int>> IntervalInsection(vector<vector<int>> &A, vector<vector<int>> &B)
    {
        int i, j = 0;
        vector<vector<int>> result;
        while (i < A.size() && j < B.size())
        {
            int aInStart = A[i][0];
            int aInEnd = A[i][1];

            int bInStart = B[i][0];
            int bInEnd = B[i][1];
            if (bInStart < aInEnd && aInStart < bInEnd)
            {
                result.push_back({max(aInStart, bInStart), min(aInEnd, bInEnd)});
            }
            if(bInEnd < aInEnd)//谁小谁加1
            {
                j++;
            }
            else
            {
                i++;
            }
        }
        return result;
    }
};

int main()
{
    return 0;
}
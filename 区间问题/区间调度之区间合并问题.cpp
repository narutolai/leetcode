#if 0
����һЩ���� Ȼ��ϲ����е����� ���������н����ͺϲ�
����:[[1,3],[3,6],[8,10],[15,18]]
���:[[1,6],[8,10],[15,18]]

���� [1,3]��[3,6]����ϲ���.
#endif
#include <vector>
#include <algorithm>
using namespace std;
class Solution
{
public:
    vector<vector<int>> MergeInterVal(vector<vector<int>> &intervals)
    {
        vector<vector<int>> result;

        sort(intervals.begin(), intervals.end());
        //�Ȱѵ�һ��ѹ������
        result.push_back(intervals[0]);
        //����ʣ�������
        for (auto &interval : intervals)
        {
            auto &last = result.back();
            if (interval[0] <= last[1])
            {
                last[1] = max(last[1], interval[1]);
            }
            else
            {
                result.push_back(interval);
            }
        }
        return result;
    }
};
//�о����������ok ��֪���ɲ��������ڱ��������������
#include<iostream>
// �������start����Ϳ���
int main()
{
    Solution so;
    vector<vector<int>> temp = {{1, 3}, {3, 6}, {8, 10}, {15, 18}};
    vector<vector<int>> result = so.MergeInterVal(temp);
    for(auto &item :result)
    {
        cout<<item[0]<<" "<<item[1]<<endl;
    }
    return 0;
}
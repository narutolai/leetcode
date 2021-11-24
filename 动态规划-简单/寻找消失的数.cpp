#include <vector>
#include <iostream>

using namespace std;

//给定一个包含0 ，1，2，，，n中n个数的序列 找出 0-n中没有出现在序列中的那个数
//异或运算 同0异1的规则
class Solution
{
public:
    int missNumber(vector<int> &num)
    {
        int n = num.size();
        int res = 0;
        res ^= n;
        for (int i = 0; i < n; i++)
        {
            res ^= i ^ num[i];
        }
        return res;
    }
};

int main()
{
}
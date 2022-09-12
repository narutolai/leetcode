#include <vector>
#include <iostream>

using namespace std;

//给定一个包含0 ，1，2，，，n中n个数的序列 找出 0-n中没有出现在序列中的那个数
//异或运算 同0异1的规则
class Solution
{
public://给定n个数 下标 是0- n-1
    int missNumber(vector<int> &num)//因为0 1 2 3 4 5中的数其实是有n+1 个数的但是却只有n个数 所以我们说少了一个数。
    {
        int n = num.size();
        int res = 0;
        res ^= n;//先异或一下n然后
        for (int i = 0; i < n; i++)
        {
            res ^= i ^ num[i];
        }
        return res;
    }
};
// 就是从0-n 这个n+1个数中选n个数，假设一个萝卜一个坑的话，那么就应该有n+1个坑位，所以下标是0--->n，
//在换句话说 实际上是从0---->n这个 n+1个坑位上选了 n个人，每个数和坑位标号相异或，剩下的数就是没有出现在序列中的数
int main()
{

}
//遍历次数 3
//一个数跟他自己异或的值是0
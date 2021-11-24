#include <vector>
#include <iostream>

using namespace std;

class UF
{
private:
    int count; //联通分量
    vector<int> parents;
    vector<int> size = 0; //记录树的重量
public:
    UF(int n) : count(n)
    {
        for (int i = 0; i < n; i++)
        {
            parents[i] = i; //起初每一个节点的根节点都是自己
            size[i] = 1;    //每一个节点的size都为1
        }
    }
    void Union(int p, int q) //连接p、q两个节点
    {
        int rootp = find(p);
        int rootq = find(q);
        if (rootp == rootq)
            return;

        if (size[rootp] > size[rootq])
        {
            parents[rootq] = rootp;
            size[rootp] += size[rootq];
        }
        else
        {
            parents[rootp] = rootq;
            size[rootq] += size[rootp];
        }
        count--;
    }
    int find(int x) //返回一个节点的根节点
    {   
        while (parents[x] != x)
        {
            parents[x] = parents[parents[x]];
            x = parents[x]; //这个
        }
        return x;
    }
    int count()
    {
        return count;
    }
};

int main()
{
}
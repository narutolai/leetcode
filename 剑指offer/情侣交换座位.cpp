// N 对情侣坐在连续排列的 2N 个座位上，想要牵到对方的手。 计算最少交换座位的次数，以便每对情侣可以并肩坐在一起。
//一次交换可选择任意两人，让他们站起来交换座位。
// 人和座位用 0 到 2N-1 的整数表示，情侣们按顺序编号，第一对是 (0, 1)，第二对是 (2, 3)，以此类推，最后一对是 (2N-2, 2N-1)。
// 这些情侣的初始座位  row[i] 是由最初始坐在第 i 个座位上的人决定的。

// 示例 1:

// 输入: row = [0, 2, 1, 3]
// 输出: 1
// 解释: 我们只需要交换row[1]和row[2]的位置即可。
// 示例 2:

// 输入: row = [3, 2, 0, 1]
// 输出: 0
// 解释: 无需交换座位，所有的情侣都已经可以手牵手了。
// 并查集 ！！
//使用 并查集 联通图做，N-.getcount()   减去联通分量

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

class Solution
{
public:
    int minSwapsCouples(vector<int> &row)
    {
        int size = row.size();
        UF uf(size / 2);
        for (int i = 0; i < row; i += 2)
        {
            uf.Union(row[i], row[i + 1]);
        }
        return size - uf.count();
    }
};
//遍历次数1 要想牵手 情侣必须要相邻
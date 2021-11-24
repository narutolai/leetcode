class Solution
{
public:
    int maxDepth(Node *root)
    {
        int maxi = 0;
        if (!root)
            return 0;
        //找出所有子树中最高的那个的长度
        for (Node *it : root->children)
        {
            if (it)
                maxi = max(maxi, maxDepth(it));
        }
        //树的长度等于最高的子树的长度+1
        return maxi + 1;
    }
};
// 时间复杂度：每个节点遍历一次，所以时间复杂度是 O(N)，其中 N 为节点数。
// 空间复杂度：最坏情况下, 树完全非平衡，
// 例如 每个节点有且仅有一个孩子节点，递归调用会发生 NN 次（等于树的深度），所以存储调用栈需要 O(N)O(N)。
// 但是在最好情况下（树完全平衡），树的高度为 \log(N)log(N)。
// 所以在此情况下空间复杂度为 O(\log(N))O(log(N))。

//我自己写的 只会使用全局变量的菜鸟
class Solution
{
    int maxDepth_ = 0;
    int depth = 1;

public:
    //就是深度优先搜索了
    void dfs(Node *root)
    {
        if (root == nullptr)
            return;

        if (depth > maxDepth_)
            maxDepth_ = depth;

        for (auto p : root->children)
        {
            depth += 1;
            dfs(p);
            depth -= 1;
        }
    }
    int maxDepth(Node *root)
    {
        dfs(root);
        return maxDepth_;
    }
};

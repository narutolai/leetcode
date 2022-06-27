class Solution
{
public:
    //BST转双向链表
    TreeNode *head, *pre; //俩个游标 root 就是cur  真的是一语惊醒梦中人，root就是cur!!!!!!
    void dfs(TreeNode *cur)
    {
        if (!cur)
            return;
        dfs(cur->left);

        if (pre == nullptr)
        {
            head = cur;
        }
        else
        {
            pre->right = cur;
        }
        //哇  这个题 真的让我 醍醐灌顶了 尤其是这个cur.......迭代法也不过如此吧。
        cur->left = pre;
        pre = cur;

        dfs(cur->right);
    }
}
//遍历次数 1
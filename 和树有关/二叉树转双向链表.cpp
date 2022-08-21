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
//遍历次数 2这题目我做10遍都不为过,一个中序遍历而已
//记住前一个节点,双向链表不是有一个 prev和next吗 这个就是把prev和next当成  left和right了。
//right 就是next  left就是prev！！！！！！！
//迭代法！！
//函数栈只是一种跳转！！！ 左 中 右！！！
//头节点时，pre=nullptr, head = cur 确定双向链表的头节点
// cur->prev =pre, pre = cur, pre->right = cur
//   pre->next = cur;
//   cur->prev = pre;
//   pre = cur;卧槽！！！！真的是服了 我真的是服了
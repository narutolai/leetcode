//先把我自己写的放过来，用的双重递归
class Solution
{
    bool flag = false; //只要有一个成功就设置其为true
public:
    void dfs(ListNode *head, TreeNode *root)
    {
        if (root)
        { //我觉得也可以演化成双重递归的意思
            if (root->val == head->val)
                if (dfs2(head, root))
                {
                    flag = true;
                    return;
                };
            dfs(head, root->left);
            dfs(head, root->right);
        }
    }
    bool dfs2(ListNode *head, TreeNode *root)
    {
        if (head == NULL)
            return true;
        if (head != NULL && root == NULL)
            return false;
        if (head->val == root->val)
            return dfs2(head->next, root->left) || dfs2(head->next, root->right);
        else
            return false;
    }

    bool isSubPath(ListNode *head, TreeNode *root)
    {
        dfs(head, root);
        return flag;
    }
};
#if 0
枚举二叉树中的每个节点为起点往下的路径是否有与链表相匹配的路径。为了判断是否匹配我们设计一个递归函数 dfs(rt,\textit{head})dfs(rt,head) ，其中 rtrt 表示当前匹配到的二叉树节点，headhead 表示当前匹配到的链表节点，
整个函数返回布尔值表示是否有一条该节点往下的路径与 headhead 节点开始的链表匹配，如匹配返回 \textit{true}true，否则返回 \textit{false}false ，一共有四种情况：
链表已经全部匹配完，匹配成功，返回 \textit{true}true
二叉树访问到了空节点，匹配失败，返回 \textit{false}false
当前匹配的二叉树上节点的值与链表节点的值不相等，匹配失败，返回 \textit{false}false
前三种情况都不满足，说明匹配成功了一部分，我们需要继续递归匹配，所以先调用函数 dfs(rt\rightarrow left,head\rightarrow next)dfs(rt→left,head→next) ，
其中 rt\rightarrow leftrt→left 表示该节点的左儿子节点， head\rightarrow nexthead→next 表示下一个链表节点，如果返回的结果是 \textit{false}false，说明没有找到相匹配的路径，需要继续在右子树中匹配，
继续递归调用函数 dfs(rt\rightarrow right,head\rightarrow next)dfs(rt→right,head→next) 去找是否有相匹配的路径，
其中 rt\rightarrow rightrt→right 表示该节点的右儿子节点， head\rightarrow nexthead→next 表示下一个链表节点。
匹配函数确定了，剩下只要枚举即可，从根节点开始，如果当前节点匹配成功就直接返回 \textit{true}true ，否则继续找它的左儿子和右儿子是否满足，
也就是代码中的 dfs(root,head) || isSubPath(head,root->left) || isSubPath(head,root->right) ，然后不断的递归调用。
这样枚举所有节点去判断即能找出是否有一条与链表相匹配的路径
#endif
class Solution
{
    bool dfs(TreeNode *rt, ListNode *head)
    {
        // 链表已经全部匹配完，匹配成功
        if (head == NULL)
            return true;
        // 二叉树访问到了空节点，匹配失败
        if (rt == NULL)
            return false;
        // 当前匹配的二叉树上节点的值与链表节点的值不相等，匹配失败
        if (rt->val != head->val)
            return false;
        return dfs(rt->left, head->next) || dfs(rt->right, head->next);
    }

public:
    bool isSubPath(ListNode *head, TreeNode *root)
    {
        if (root == NULL)
            return false;
        return dfs(root, head) || isSubPath(head, root->left) || isSubPath(head, root->right);
    }
};

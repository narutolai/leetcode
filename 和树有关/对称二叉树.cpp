/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution
{
public:
    //假装是判断两颗树 每一个函数都做了自己该做的事情
    bool dfs(TreeNode *p1, TreeNode *p2)
    {
        if (p1 == NULL && p2 == NULL)
            return true; //两者皆空
        if (p1 == NULL || p2 == NULL || p1->val != p2->val)
            return false; //一个为空

        //镜面对称就是p1的左和p2的右，p1的右和p2的左边
        return dfs(p1->left, p2->right) && dfs(p1->right, p2->left);
    }
    bool isSymmetric(TreeNode *root)
    {
        if (!root)
            return true; //空树也是对称树
        return dfs(root->left, root->right);
    }
};
//遍历次数 1 
//问你一颗二叉树对不对称,从两个子节点开始啊
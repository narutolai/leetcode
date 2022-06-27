//给的一颗二叉树，返回L和R范围之间的数的和 包括其本身。
//其实就是先序遍历了
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
    int res;
public:
    void preorder(TreeNode *root, int l, int r)
    {
        if (!root)
            return;
        if (r >= root->val && root->val >= l) //判断是否在范围内
            res += root->val;
        preorder(root->left, l, r);
        preorder(root->right, l, r);
    }
    int rangeSumBST(TreeNode *root, int L, int R)
    {
        preorder(root, L, R);
        return res;
    }
};
//这道题目就是一个先序遍历的啊
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

//可以用二叉树的深度来解答
class Solution
{
    bool flag;

public:
    int dfs(TreeNode *root)
    {
        if (!root)
            return 0;
        int leftdepth = dfs(root->left);
        int rightdepth = dfs(root->right);
        if (abs(leftdepth - rightdepth) > 1) //如果左右子树深度之差大于1则返回false
            flag = false;
        return max(leftdepth, rightdepth) + 1;
    }

    bool isBalanced(TreeNode *root)
    {
        flag = true;
        dfs(root);
        return flag;
    }
};
//遍历次数 1
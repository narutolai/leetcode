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
    TreeNode *mirrorTree(TreeNode *root)
    {
        if (!root)
            return NULL;

        TreeNode *temp = root->right;
        root->right = root->left;
        root->left = temp;

        mirrorTree(root->left);
        mirrorTree(root->right);
        return root;
    }
};
//地址是用来寻找的啊 寻址 寻址 寻址！！
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
    TreeNode *searchBST(TreeNode *root, int val)
    {
        /*  递归方式*/
        if (root == NULL || root->val == val)
            return root;
        return val < root->val ? searchBST(root->left, val) : searchBST(root->right, val);
        //迭代方式
        /*
                while(root!=NULL&&root->val!=val)
                {
                    root=root->val>val?root->left:root->right;
                }
                return root;*/
    }
}
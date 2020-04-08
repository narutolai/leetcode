/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
//关键是 怎么判断一节点是左叶子节点。
class Solution {
public:
    int sumOfLeftLeaves(TreeNode* root) {
        if(root==NULL) return NULL;
        //先判断左节点存在才可以去判断
        if(root->left!=NULL&&root->left->left==NULL&&root->left->right==NULL)
              return root->left->val+sumOfLeftLeaves(root->right);
        return sumOfLeftLeaves(root->left)+sumOfLeftLeaves(root->right);
    }
};

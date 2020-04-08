//给定一颗二叉搜索树，然后每个节点的值要加上所有比它大的节点的和。
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
 //二叉搜索树从右到左边遍历，然后再遍历的过程中做处理
class Solution {
    int presum=0; //从右边到左遍历
public:
    TreeNode* convertBST(TreeNode* root) {
        if(root)
        {
            convertBST(root->right);//不一样的中序遍历
            root->val+=presum;
            presum=root->val;
            convertBST(root->left);
        }
        return root;
    }
};

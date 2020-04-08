/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {

        //二叉树先序遍历
        if(t1==NULL) return t2;
        if(t2==NULL) return t1; //三个返回值  以及其他操作
        //合并根节点
        t1->val+=t2->val;
        //递归合并左右子树
        t1->left=mergeTrees(t1->left,t2->left);
        t1->right=mergeTrees(t1->right,t2->right);

    return t1;
    }
};

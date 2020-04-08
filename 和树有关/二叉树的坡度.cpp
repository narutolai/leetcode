/*
给定一个二叉树，计算整个树的坡度。

一个树的节点的坡度定义即为，该节点左子树的结点之和和右子树结点之和的差的绝对值。空结点的的坡度是0。

整个树的坡度就是其所有节点的坡度之和。
*/
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
    int sum; //后序遍历
public:

    int depth(TreeNode*root){
        if(root==NULL) return 0;
        int leftsum=depth(root->left);
        int rightsum=depth(root->right);
        //节点要做什么：要累加坡度
        sum+=leftsum>rightsum?leftsum-rightsum:rightsum-leftsum;
        //此节点返回什么，返回节点之和
        return root->val+leftsum+rightsum;
    }
    int findTilt(TreeNode* root) {
        sum=0;
        depth(root);   
        return sum;
    }
};

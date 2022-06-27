/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
 //可以采用N叉树的遍历方法只是改个就行了 后续遍历使用两个栈 
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        stack<TreeNode*> st1;
        stack<TreeNode*> st2;
        vector<int> res;
        if(!root) return res;
        st1.push(root);
        while(!st1.empty())
        {
            TreeNode *temp=st1.top();
            st1.pop();

            st2.push(temp);

            if(temp->left)
             st1.push(temp->left);
             if(temp->right)
             st1.push(temp->right);
        }
        while(!st2.empty())
        {
            TreeNode *temp=st2.top();
            st2.pop();
            res.push_back(temp->val);
        }
        return res;
    }
};
//遍历次数 1
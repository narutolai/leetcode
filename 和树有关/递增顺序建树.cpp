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
    void midorder(TreeNode *p,vector<int> &res)
    {
        if(!p)return ;
        midorder(p->left,res);
        res.push_back(p->val);
        midorder(p->right,res);
    }
    TreeNode* increasingBST(TreeNode* root) {
            //注意这是一颗bst
            //要重新构建一颗二叉树啊
        vector<int> res;
        midorder(root,res);
        TreeNode *cur;
        TreeNode* head = new TreeNode(res[0]);
        cur=head;
        for(int i=1;i<res.size();i++)
        {
            cur->right=new TreeNode(res[i]); //差点忘记了怎么建树了
            cur=cur->right;
        }
        return head;
    }
};

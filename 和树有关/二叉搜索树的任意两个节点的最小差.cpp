/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
 //因为是二叉搜索树，所以i可以中序遍历得到一个递增序列，然后在求两个相邻的数的差值中找到最小。
 //也可以在中序递归的过程中解决吧
class Solution {
    vector<int> res;
public:
    int getMinimumDifference(TreeNode* root) {
        midorder(root);
        int min_abs=INT_MAX;
        for(int i=1;i<res.size();i++)
        {
            min_abs=min(res[i]-res[i-1],min_abs);
        }
        return min_abs;
    }
    void midorder(TreeNode*root)
    {if(root)
    {
        midorder(root->left);
        res.push_back(root->val);
        midorder(root->right);
    }
    }
};

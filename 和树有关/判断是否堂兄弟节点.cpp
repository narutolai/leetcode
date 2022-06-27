/*
什么是堂兄弟节点？
深度相同但是父节点不同
所有解决办法是找到节点所处的深度和其父节点，看满不满足上述陈述。
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
//
class Solution
{
    TreeNode *parent1 = NULL;
    TreeNode *parent2 = NULL;
    int depth1 = -1;
    int depth2 = -1;

public:
    void dfs(TreeNode *root, int x, int y, int h)
    {
        if (!root)
            return;

        if (root->left && root->left->val == x)
        {
            parent1 = root, depth1 = h;
            return;
        }
        if (root->right && root->right->val == x)
        {
            parent1 = root, depth1 = h;
            return; 
        }

        if (root->left && root->left->val == y)
        {
            parent2 = root, depth2 = h;
            return;
        }
        if (root->right && root->right->val == y)
        {
            parent2 = root, depth2 = h;
            return;
        }

        dfs(root->left, x, y, h + 1);
        dfs(root->right, x, y, h + 1);
    }
    bool isCousins(TreeNode *root, int x, int y)
    {
        dfs(root, x, y, 0);
        return (depth2 == depth1) && (parent1 != parent2);
    }
};
//
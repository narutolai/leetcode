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
    int sum;

public:
    void dfs(TreeNode *root, int pre)
    {
        if (!root)
            return;
        int cur_sum = pre * 2 + root->val;
        if (root->left == NULL && root->right == NULL)
        { //到了叶子节点就把最终结果累加
            sum += cur_sum;
            return;
        }
        pre = cur_sum;
        dfs(root->left, pre);
        dfs(root->right, pre);
    }
    int sumRootToLeaf(TreeNode *root)
    {
        dfs(root, 0);
        return sum;
    }
};

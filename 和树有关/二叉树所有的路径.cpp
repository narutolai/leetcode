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
    string path;
    vector<string> res;

public:
    vector<string> binaryTreePaths(TreeNode *root)
    {
        backtrace(root);
        return res;
    }
    void backtrace(TreeNode *root)
    {
        if (!root)
            return;
        int len = path.size(); //记录进入节点前的长度
        path += (path.empty() ? "" : "->") + to_string(root->val);

        if (!root->left && !root->right) //到了叶子节点处
        {
            res.push_back(path);  //注意 这个后面不能加return的啊
        }
        backtrace(root->left);
        backtrace(root->right);
        path.erase(path.begin() + len, path.end()); //撤销选择
    }
};

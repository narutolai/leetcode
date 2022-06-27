/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
//层次遍历二叉树，中规中矩的使用队列就行了，反正也是一出队列 一入队列
//记录每一层的节点个数
class Solution
{
public:
    vector<vector<int>> levelOrder(TreeNode *root)
    {
        queue<TreeNode *> qu;
        qu.push(root);
        TreeNode *cur;
        vector<vector<int>> result;
        if (!root)
            return result;
        while (!qu.empty())
        {
            int n = qu.size();
            vector<int> temp;
            for (int i = 0; i < n; i++)
            {
                cur = qu.front();
                qu.pop();
                temp.push_back(cur->val);

                if (cur->left)
                    qu.push(cur->left);
                if (cur->right)
                    qu.push(cur->right);
            }
            result.push_back(temp);
        }
        return result;
    }
};

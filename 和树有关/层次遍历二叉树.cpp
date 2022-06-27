//从下到上 从左到右遍历二叉树
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
public:
    vector<vector<int>> levelOrderBottom(TreeNode *root)
    {
        vector<vector<int>> res;
        if (!root)
            return res; //如果为空 则返回空数组
        queue<TreeNode *> qu;
        TreeNode *cur = root;
        qu.push(cur);
        while (!qu.empty())
        {
            int size = qu.size();//当前层有多少个元素
            vector<int> level;
            for (int i = 0; i < size; i++)
            {
                cur = qu.front();
                qu.pop();
                level.push_back(cur->val);
                if (cur->left)
                    qu.push(cur->left);
                if (cur->right)
                    qu.push(cur->right);
            }
            res.push_back(level);
        }
        reverse(res.begin(), res.end()); //最后逆置一下嘿嘿
        return res;
    }
};
//遍历次数 1
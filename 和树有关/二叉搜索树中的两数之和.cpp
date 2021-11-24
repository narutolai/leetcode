/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
//先中序遍历，然后用双指针来求两数之和，当然也可以用哈希表来快速求解吧
class Solution
{
    vector<int> res;

public:
    void midorder(TreeNode *p)
    {
        if (p)
        {
            midorder(p->left);
            res.push_back(p->val);
            midorder(p->right);
        }
    }
    //等于是递增序列中求两数之和。
    bool findTarget(TreeNode *root, int k)
    {
        midorder(root);
        int i = 0, j = res.size() - 1;
        while (i < j)
        {
            if (res[i] + res[j] == k)
                return true;
            else if (res[i] + res[j] > k)
                j--;
            else
                i++;
        }
        return false;
    }
};

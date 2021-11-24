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
    //查
    TreeNode *searchBST(TreeNode *root, int val)
    {
        /*  递归方式*/
        if (root == NULL || root->val == val)
            return root;
        return val < root->val ? searchBST(root->left, val) : searchBST(root->right, val);
    }
    //二叉搜索树的增
    TreeNode *addNode(TreeNode *root, int val)
    {
        if (root == nullptr)
            return new TreeNode(val);
        else if (root->val > val)
            root->left = addNode(root->left, val);
        else if (root->val < val)
            root->right = addNode(root->right, val);
        return root;
    }
    //二叉搜索树的删
    TreeNode *getMin(TreeNode *root)
    {
        while (root->left)
        {
            root = root->left;
        }
        return root;
    }
    TreeNode *deleteNode(TreeNode *root, int val)
    {
        if (root == nullptr) //找不到 就没用了
            return nullptr;
        else if (root->val == val)
        {
            if (root->left && root->right)
            {
                //获取最小点 代替
                TreeNode *min = getMin(root->right);
                swap(root->val, min->val);
                root->right = deleteNode(root->right, val);
            }
            else if (root->left)
            {

                return root->left;
            }
            else if (root->right)
            {
                return root->right;
            }
            else
            {
                return nullptr;
            }
        }
        else if (root->val > val)
            root->left = deleteNode(root->left, val);
        else if (root->val < val)
            root->right = deleteNode(root->right, val);
        return root;
    }
}

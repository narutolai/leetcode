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
    //获取二叉搜索树的最小节点
    TreeNode *getMin(TreeNode *root)
    {
        while (root->left)
        {   
            root = root->left;
        }
        return root;
    }
     //二叉搜索树的删
    TreeNode *deleteNode(TreeNode *root, int val)
    {
        if (root == nullptr) //找不到 就不需要删了
            return nullptr;
        else if (root->val == val)
        {
            if (root->left && root->right)
            {
                //获取最小点 代替
                TreeNode *min = getMin(root->right);//替换 删除 
                swap(root->val, min->val);
                root->right = deleteNode(root->right, val);//替换 删除 替换删除!!!!!
            }
            else if (root->left)
            {
                return root->left;//拼接
            }
            else if (root->right)
            {
                return root->right;//拼接
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
//遍历次数 2 
//是二叉搜索树的 查 增 删
//可以  也有意思 多做做！！写完了！
//我们知道 合格的二叉搜索树 必须保证 每一个节点大于其左子树最大值，小于右子树 最小值。
//可是这还不够

class Solution
{
public:
    bool isValidBST(TreeNode *root)
    {
        return isValidBST(root, nullptr, nullptr);
    }
    //从根节点开始 min 是升序遍历root左边那个数，max是root右边那个数
    //在遍历过程中我们需要时刻保证 min < root < max  才对的。
    bool isValidBST(TreeNode *root, TreeNode *min, TreeNode *max)
    {
        if (!root)
            return true;
        if (min && root->val <= min->val)
            return false;
        if (max && root->val >= max->val)//不能等于的吗
            return false;
        return isValidBST(root->left, min, root) && isValidBST(root->right, root, max);
    } //左中右
    //
}

//其实这道题有点想不明白的

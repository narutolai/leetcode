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

/**
 * 只需要关注左子树当中最大值和右子树当中最小值就行了。如果左子树当中的最大值也小于根节点，右子树当中的最小值也大于根节点，
 * 那么就一定是合法的。反过来如果左子树存在比根节点大的数或者是右子树存在比根小的数就都是非法的。
 * 我们可以通过递归来同时维护当前子树当中的最大值和最小值，只要用左子树的最大值和右子树的最小值和根节点进行校验即可。
*/
//二叉搜索树的一个特点，左子树最大值是左子树最右边的,左子树最小值是最左边的。
//要求是 左子树最大值小于根节点，右子树最小值大于根节点！！！其实是这样
//错误的解法是  root->val > root-left->val  &&  root->val <root->right->val;
//正确的解法是 root->val > max(左子树)[而左子树的最大值就是左子树最右边节点] && root->val < min(右子树，右子树最小值就是右子树最左边)
//无法理解题目做法的根本原因可能是自己根本没有懂题目的意思。。。。

//另一个解法！！先中序遍历 然后看是否满足升序......................................... 啊这 啊这  啊这 啊这  啊这....
/*给定一个二叉搜索树, 找到该树中两个指定节点的最近公共祖先。
百度百科中最近公共祖先的定义为：“对于有根树 T 的两个结点 p、q，最近公共祖先表示为一个结点 x，
满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”
*/
/*
如果p q的值都大于父节点，那么就在其右子树搜索
如果都小于父节点，那么就在其左子树搜索
如果一个大一个小，该父节点就是最近祖先
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
class Solution
{
public:
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        if (root == NULL)
            return NULL;
        if (root->val > p->val && root->val > q->val) //说明p，q都在左子树
            return lowestCommonAncestor(root->left, p, q);
        else if (root->val < p->val && root->val < q->val) //说明p，q都在右子树
            return lowestCommonAncestor(root->right, p, q);
        else // p，q各在一边，说明当前的根就是最近共同祖先
            return root;
    }
};

//普通二叉树 其实就是个后序遍历吧
class Solution
{
public: //其实就是在二叉树里找一个节点。
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        if (root == NULL)
            return NULL;
        //如果根节点就是p或者q，返回根节点
        if (root == p || root == q)
            return root;
        //分别去左右子树里面找
        TreeNode *left = lowestCommonAncestor(root->left, p, q);
        TreeNode *right = lowestCommonAncestor(root->right, p, q);

        if (left && right) // p，q各在一边，说明当前的根就是最近共同祖先
            return root;
        else if (left) //说明p，q都在左子树
            return left;
        else if (right) //说明p，q都在右子树
            return right;
        else
            return NULL;
    }
};
//遍历次数2
//我觉得可以这样理解这个题,就是两个节点的汇聚点......
//怎么样一个节点才是pq的最近祖先呢,除非,节点的
//我靠！！！ 这个是唯一的！！！！！两个节点的最近公共祖先是唯一的！！！
//就是一个节点左子树有p ，右子树有q,这个节点是唯一存在的！！！！！有且仅仅有一个！！！！我靠！！！
//在普通二叉树中找一个节点,所以当该节点的left和right都有的时候那么就是那个唯一公共祖先！！
//遍历次数 2
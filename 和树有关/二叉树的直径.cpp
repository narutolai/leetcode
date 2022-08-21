//给定一棵二叉树，你需要计算它的直径长度。一棵二叉树的直径长度是任意两个结点路径长度中的最大值。这条路径可能穿过也可能不穿过根结点。
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution
{
public:
    int maxlenght;
    int traverse(TreeNode *root)
    {
        if (!root)
            return 0;
        int leftnum = traverse(root->left);
        int rightnum = traverse(root->right);   
        maxlenght = max(maxlenght, leftnum + rightnum + 1);
        return max(leftnum, rightnum) + 1;
    }
    int diameterOfBinaryTree(TreeNode *root)
    {
        traverse(root);
        return maxlenght - 1;
    }
};
//遍历次数 2 可能穿过根节点也可能不穿过根节点。
//我做了什么 ,我返回什么。
//任意两个节点路径长度中的最大值，就是说两个节点间可能有很多条路径我们要求其最大值。
//因为一个节点有两个分叉,既然是最长的所以肯定是要返回max(left, right) + 1
//直径和坡度
//直径和坡度
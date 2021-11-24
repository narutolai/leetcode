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

int main()
{
    return 0;
}
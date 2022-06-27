// 给定一个整数 n，生成所有由 1 ... n 为节点所组成的二叉搜索树。

// 示例:

// 输入: 3
// 输出:
// [
//   [1,null,3,2],
//   [3,2,null,1],
//   [3,1,null,null,2],
//   [2,1,3],
//   [1,null,2,null,3]
// ]
// 解释:
// 以上的输出对应以下 5 种不同结构的二叉搜索树：
// 层次遍历 
//    1         3     3      2      1
//     \       /     /      / \      \
//      3     2     1      1   3      2
//     /     /       \                 \
//    2     1         2                 3

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
    vector<TreeNode *> dfs(int start, int end)
    {
        if (start > end)
            return {NULL};
        vector<TreeNode *> ans;
        //随机选定根节点
        for (int i = start; i <= end; i++)
        { //分出左右节点数组
            vector<TreeNode *> lefts = dfs(start, i - 1), rights = dfs(i + 1, end);

            //遍历左右数组中的每一个作为根节点的左右节点
            for (auto left_ : lefts)
                for (auto right_ : rights)
                {
                    TreeNode *root = new TreeNode(i);
                    root->left = left_;
                    root->right = right_;
                    ans.push_back(root); //压入结果
                }
        }
        return ans;
    }
    vector<TreeNode *> generateTrees(int n)
    {
        //首先你要知道怎么创建二叉搜索树，
        if (n == 0)
            return {};
        return dfs(1, n);
    }
};
//遍历次数 1

#if 0
给你一棵以 root 为根的二叉树，二叉树中的交错路径定义如下：

选择二叉树中 任意 节点和一个方向（左或者右）。
如果前进方向为右，那么移动到当前节点的的右子节点，否则移动到它的左子节点。
改变前进方向：左变右或者右变左。
重复第二步和第三步，直到你在树中无法继续移动。
交错路径的长度定义为：访问过的节点数目 - 1（单个节点的路径长度为 0 ）。
请你返回给定树中最长 交错路径 的长
#endif
 

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int ans=0;
    void dfs(TreeNode *root,int toright,int dir)
    {
        if(!root) return ;
        ans=max(ans,dir);
        if(toright)// toleft为1表示右走
        {
            dfs(root->left,0,dir+1);//下一步只有左走才可以使得交错路径加1
            dfs(root->right,1,1);   //如果下一步也是右走,那交错路径就还是从1开始计数
        }
        else
        {
            dfs(root->left,0,1);
            dfs(root->right,1,dir+1);
        }
    }
    int longestZigZag(TreeNode* root) {
        dfs(root->left,0,1); //0左1右
        dfs(root->right,1,1);
        return ans;

    }
};
//遍历次数 2

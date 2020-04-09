/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
/*
我们先使用dfs计算出整个二叉树的所有节点的和sum也就是25行
然后再运行一次dfs得到ans,这一次我们的sum不再是0
*/
class Solution {
public:
    const static int mod=1e9+7;
    long long ans=-1;
    long long sum=0;
    long long dfs(TreeNode *root)
    {
        if(root==NULL) return 0;
        long long t1=dfs(root->left),t2=dfs(root->right);
        //在递归计算左右子树的时候，顺便把结果给更新了 6啊6啊！
        ans=max(ans,max(t1*(sum-t1),t2*(sum-t2))); 
        return root->val+t1+t2;
    }  //怎么可以这么强啊 
    int maxProduct(TreeNode* root) {
            sum=dfs(root);
            dfs(root);
            return (int)(ans%mod);
    }
};

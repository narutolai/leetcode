给定一个二叉树，它的每个结点都存放着一个整数值。

找出路径和等于给定数值的路径总数。

路径不需要从根节点开始，也不需要在叶子节点结束，但是路径方向必须是向下的（只能从父节点到子节点）。
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
 //我使用的方法是双重递归，在每一个节点处都进行一次递归
class Solution {
    int count;
public:
    void dfs(TreeNode*root,int sum){
        if(!root) return ;
        if(sum-root->val==0) count++; //注意这里等于0后不需要返回，因为可能有负值出现[1,-2,-3,1,3,-2,null,-1]

        dfs(root->left,sum-root->val);
        dfs(root->right,sum-root->val);
    }
    int pathSum(TreeNode* root, int sum) {
        
        if(!root) return 0;
        dfs(root,sum);
        pathSum(root->left,sum);
        pathSum(root->right,sum);
        return count;
    }
};
/*还可以使用前缀和的方法时间复杂度为O(n) n为树的节点个数
遍历到某个节点时，在hash中查找前缀和为prefix_sum-sum的节点的个数，
结果等于这个个数加上左右子树中满足条件的节点个数
前缀和就是Sn。如果有Sn-Sn-k=target即 Sn-target=Sn-k就说明存在一条路径等于给的数值。
类似两数之和
*/

class Solution {
public:
    unordered_map<int, int> count;
    int pathSum(TreeNode* root, int sum) {
        count[0] = 1;
        return helper(root, sum, 0);
    }
    int helper(TreeNode* root, int sum, int prefix_sum) {
        if (!root) return 0;
        int res = 0;
        prefix_sum += root->val;
        res += count[prefix_sum - sum];
        count[prefix_sum]++;
        res += helper(root->left, sum, prefix_sum) + helper(root->right, sum, prefix_sum);
        count[prefix_sum]--;
        return res;
    }
};

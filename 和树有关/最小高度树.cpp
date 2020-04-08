
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
给定一个有序整数数组，元素各不相同且按升序排列，编写一个算法，创建一棵高度最小的二叉搜索树。
//递归创建每一次都选取其中点
class Solution {
public:
    TreeNode* helper(vector<int>& nums, int left,int right){
        if(left<=right)
        {int mid=(left+right)/2;
        TreeNode *root=new TreeNode(nums[mid]);
        root->left=helper(nums,left,mid-1);
        root->right=helper(nums,mid+1,right);
        return root;
        }
        return NULL;
    }

    TreeNode* sortedArrayToBST(vector<int>& nums) {
            return helper(nums,0,nums.size()-1);
    }
};

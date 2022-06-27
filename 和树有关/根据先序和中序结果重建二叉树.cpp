
//核心是 先序是 中 左 右
//      中序    左 中 右
//      后序    左 右 中
//
class Solution
{
public://根据先序和中序来建立二叉树
    TreeNode *createByFC(map<int, int> &num2index, vector<int> &nums1, int st1, int et1, vector<int> &nums2, int st2, int et2)
    {
        if (st1 > et1 || st2 > et2) //这里写哪个都可以 因为
            return nullptr;
        //找到先序序列第一个数在 中序序列中的下标
        int index = num2index[nums1[st1]];
        int length = index - st2;
        TreeNode *root = new TreeNode(nums1[st1]);
        root->left = createByFC(num2index, nums1, st1 + 1, st1 + length, nums2, st2, index - 1);
        root->right = createByFC(num2index, nums1, st1 + length + 1, et1, nums2, index + 1, et2);
        return root;
    }


    //根据后序和中序来建立二叉树                    
     TreeNode *createByFC(map<int, int> &num2index, vector<int> &nums1, int st1, int et1, vector<int> &nums2, int st2, int et2)
    {
        if (st1 > et1 || st2 > et2) //这里写哪个都可以 因为
            return nullptr;
        //找到后序序列最后一个数在 中序序列中的下标
        int index = num2index[nums1[et1]];
        //左部分的长度
        int length = index - st2;
        TreeNode *root = new TreeNode(nums1[et1]);
        root->left = createByFC(num2index, nums1, st1 , st1 + length-1, nums2, st2, index - 1);
        root->right = createByFC(num2index, nums1, st1 + length , et1-1, nums2, index + 1, et2);
        return root;
    }
}
//遍历次数 1
// st1                  et1
//  1   2  4  5  3  6   7
// 4 2 5 1 6 3 7
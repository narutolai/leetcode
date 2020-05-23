在一个 n * m 的二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。

 

示例:

现有矩阵 matrix 如下：

[
  [1,   4,  7, 11, 15],
  [2,   5,  8, 12, 19],
  [3,   6,  9, 16, 22],
  [10, 13, 14, 17, 24],
  [18, 21, 23, 26, 30]
]
给定 target = 5，返回 true。

给定 target = 20，返回 false。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/er-wei-shu-zu-zhong-de-cha-zhao-lcof
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。


class Solution {
public:
    bool  find(vector<int>& num,int target)
    {
        int left=0,right=num.size()-1;
        while(left<=right)
        {
            int mid=(left+right)/2;
            if(num[mid]>target) right=mid-1;
            else if(num[mid]<target) left=mid+1;
            else return true;
        }
        return false;
    }
    bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
        //二维二分法？？ 起始就是在每一维度用一个
        for(int i=0;i<matrix.size();i++)
        {
            if(find(matrix[i],target)) {return true;break;}
        }
        return false;
    }
};

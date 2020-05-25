class Solution {
public:
    //旋转数组中找最小值
    int minArray(vector<int>& numbers) {
        int left=0,right=numbers.size()-1;

       //决定这么操作的根本原因在于它是要在一个递增数组中找最小值。
       //确定旋转点。
        while(left<right)
        {   
            int mid=(left+right)/2;                       //  l     mid      r
            //如果中间数小于最右边的 那么最小值就在[left,mid]     5  6  1  2  3  4
            if(numbers[mid]<numbers[right]) right=mid;
            //如果中间数大于最右边的 那么旋转点就在[mid+1,right]  3  4  5  6  1  2
            else if(numbers[mid]>numbers[right]) left=mid+1;
            else right--; //去重
        }
        return numbers[left];
    }
};

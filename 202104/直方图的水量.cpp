//接雨水问题
//3.双指针
class Solution
{
public:
    int trap(vector<int> &height)//直方图的水量
    {
        int sum = 0;
        int n = height.size();
        int i = 0, j = n - 1;
        int left_max = 0, right_max = 0;
        while (i < j)
        {
            left_max = max(left_max, height[i]);
            right_max = max(right_max, height[j]);
            if (height[i] < height[j]) //如果height[i]<height[j] 那么left_max<right_max ,本来就是用左右两边的最小值去减去那个值
            {
                sum += left_max - height[i];
                i++:
            }
            else
            {
                sum += right_max - height[j];
                j--;
            }
        }
        return sum;
    }
};
//遍历次数 2
class Solution
{
public:
    int maxArea(vector<int> &height)//盛水最多的容器
    {
        int l = 0, r = height.size() - 1;
        int res = 0;
        while (l < r)
        {
            int area = min(height[l], height[r]) * (l - r);//1

            res = max(area, res);
            if (height[l] < height[r])
            {
                l++;
            }
            else    
            {
                r--;
            }
        }
        return res;
    }
};
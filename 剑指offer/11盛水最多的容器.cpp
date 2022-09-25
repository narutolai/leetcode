
// 给你 n 个非负整数 a1，a2，...，an，每个数代表坐标中的一个点 (i, ai) 。在坐标内画 n 条垂直线，垂直线 i 的两个端点分别为 (i, ai) 和 (i, 0) 。
//找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。

// 说明：你不能倾斜容器。
//注意 这道题 只是要你找出其中的两个数  使得min(height[l], height[r]) * (r - l)面积可以最大
//这个题目和接雨水问题是不一样的。细看就知道为什么不一样了。
class Solution
{
public:
    int maxArea(vector<int> &height)
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
//注意这道题要和直方图的水量(202104中,去年4月份竟然在写leetcode题哈哈)区分开来
//遍历方式1
//为什么这么做是可行的,我们最终是要求出最大值,如果采用暴力法,我们应该要比较 (n+1)n/2 个 area,然后从中获取最大值
//但是通过这种方式我们只需要比较n个area 就行了。这是为什么呢，因为这种方式每次获取的area 一定是以min(height[l], height[r])为
//高的所有矩形里面积最大的。我们从多个最大area里找最大area 这样就避免了不必要的area比较
class Solution
{
public:
    int trap(vector<int> &height)
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
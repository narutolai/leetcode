
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
        while (l < r)
        {
            int area = min(height[l], height[r]) * (l - r);

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
    }
};

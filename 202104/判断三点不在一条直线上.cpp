// 回旋镖定义为一组三个点，这些点各不相同且不在一条直线上。

// 给出平面上三个点组成的列表，判断这些点是否可以构成回旋镖。

//  

// 示例 1：

// 输入：[[1,1],[2,3],[3,2]]
// 输出：true
// 示例 2：

// 输入：[[1,1],[2,2],[3,3]]
// 输出：false

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/valid-boomerang
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

//计算直线方程
class Solution
{
public: //直线方程
    bool isBoomerang(vector<vector<int>> &points)
    {
        //处理重复点
        if (points[0] == points[1] ||
            points[0] == points[2] ||
            points[1] == points[2])
            return false;
        //处理垂线
        if (points[0][0] - points[1][0] == 0)
        {
            return points[0][0] != points[2][0];
        }
        if (points[2][1] == (points[1][1] + (points[0][1] - points[1][1]) * (points[2][0] - points[1][0]) / float(points[0][0] - points[1][0])))
            return false;

        return true;
    }
};
//三角型两边之和大于第三边

// 在一个 n * m 的二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。
// 请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。

//  

// 示例:

// 现有矩阵 matrix 如下：

// [
//   [1,   4,  7, 11, 15],
//   [2,   5,  8, 12, 19],
//   [3,   6,  9, 16, 22],
//   [10, 13, 14, 17, 24],
//   [18, 21, 23, 26, 30]
// ]
// 给定 target = 5，返回 true。

// 给定 target = 20，返回 false。

// 由于给定的二维数组具备每行从左到右递增以及每列从上到下递增的特点，
//当访问到一个元素时，可以排除数组中的部分元素。

// 从二维数组的右上角开始查找。如果当前元素等于目标值，则返回 true。
// 如果当前元素大于目标值，则移到左边一列。如果当前元素小于目标值，则移到下边一行。

//可以证明这种方法不会错过目标值。如果当前元素大于目标值，说明当前元素的下边的所有元素都一定大于目标值，
//因此往下查找不可能找到目标值，往左查找可能找到目标值。
//如果当前元素小于目标值，说明当前元素的左边的所有元素都一定小于目标值，
//因此往左查找不可能找到目标值，往下查找可能找到目标值。

// [
//   [1,   4,  7, 11, 15],
//   [2,   5,  8, 12, 19],
//   [3,   6,  9, 16, 22],
//   [10, 13, 14, 17, 24],
//   [18, 21, 23, 26, 30]
// ]
// 若数组为空，返回 false
// 初始化行下标为 0，列下标为二维数组的列数减 1
// 重复下列步骤，直到行下标或列下标超出边界
// 获得当前下标位置的元素 num
// 如果 num 和 target 相等，返回 true
// 如果 num 大于 target，列下标减 1
// 如果 num 小于 target，行下标加 1
// 循环体执行完毕仍未找到元素等于 target ，说明不存在这样的元素，返回 false`

//这个也可以线性查找
//从右上角开始 使得 我可以走的方向只有下和左
class Solution
{
public:
    bool findNumberIn2DArray(vector<vector<int>> &matrix, int target)
    {
        if (matrix.size() == 0 || matrix[0].length == 0)
        {
            return false;
        }
        int rows = matrix.length, columns = matrix[0].length;
        int row = 0, column = columns - 1;
        //从第0行开始 最后一列交叉点 那就是矩阵右上角那个点开始
        while (row < rows && column >= 0)
        {
            //右上角开始 其实从左下角开始也可以的
            int num = matrix[row][column];
            if (num == target)
            {
                return true;
            }
            else if (num > target) //如果目标数更小，那要往左1列
            {
                column--;
            }
            else
            {
                row++;  //否则往下一行，可以类比盛水容器吗
            }
        }
        return false;
    }
}
//遍历次数 2 没有细想是为什么 不过记在脑子里了
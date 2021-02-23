N 对情侣坐在连续排列的 2N 个座位上，想要牵到对方的手。 计算最少交换座位的次数，以便每对情侣可以并肩坐在一起。 一次交换可选择任意两人，让他们站起来交换座位。

人和座位用 0 到 2N-1 的整数表示，情侣们按顺序编号，第一对是 (0, 1)，第二对是 (2, 3)，以此类推，最后一对是 (2N-2, 2N-1)。

这些情侣的初始座位  row[i] 是由最初始坐在第 i 个座位上的人决定的。

示例 1:

输入: row = [0, 2, 1, 3]
输出: 1
解释: 我们只需要交换row[1]和row[2]的位置即可。
示例 2:

输入: row = [3, 2, 0, 1]
输出: 0
解释: 无需交换座位，所有的情侣都已经可以手牵手了。



class Solution {
public:
    int minSwapsCouples(vector<int>& row) {
        int count=0;
//遍历所有的偶数位置
        for (int i = 0; i < row.size(); i += 2)
    {
       //如果当前编号为奇数 找到比它小1的编号就是它情侣了
            if (row[i] % 2)
            {   if(row[i]-1!=row[i+1])
                for (int j = i + 1; j < row.size(); j++)
                    if (row[j] == row[i] - 1)
                    {
                        swap(row[j], row[i + 1]);
                        count++;
                    }
            }
            else //否则为偶数 找到比它大1的编号就是它情侣了
            {   if(row[i]+1!=row[i+1])
                for (int j = i + 1; j < row.size(); j++)
                    if (row[j] == row[i] + 1)
                    {
                        swap(row[j], row[i + 1]);
                        count++;
                    }
            }
        
    }

        return count;
    }
};


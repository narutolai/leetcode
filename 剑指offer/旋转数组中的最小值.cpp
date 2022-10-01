class Solution
{
public:
    //旋转数组中找最小值
    int minArray(vector<int> &numbers)
    {
        int left = 0, right = numbers.size() - 1;

        while (left < right)
        {
            int mid = (left + right) / 2;
            if (numbers[mid] < numbers[right])//如果中间数小于右边，那么肯定要往左边取才能获取最小值
                right = mid;
            else if (numbers[mid] > numbers[right])//如果中间数大于右边，那么右边才有最小值的啊 卧槽！！
                left = mid + 1;
            else
                right--;      //如果mid == right 为什么是right--呢 我想不明白啊
                            //通过实验我发现 最后left = right = mid的时候,就会走到这里然后right--退出循环
                            //2022-09-30
                            // 但是left == right的时候 while也不成立呀
        }
        return numbers[left];
    }
    void test()
    {
        vector<int> nums{1, 2, 3, 4, 5, 6, 7, 8};//极端情况下
        //{8,7,6,5,4,3,2,1}
        int size = nums.size();
        for (int i = 0; i < nums.size(); i++)
        {
            cout << "nums[left]" << nums[(i + 1) % size] << "  nums[mid] : " << nums[(i + size / 2) % size] << "  nums[right]: " << nums[i] << endl;
        }
    }
};
//既然是旋转数组，那么肯定是 
// 竟然可以用二分法找一个最小的数
// 二分法中一个死循环的判断
/**
 * while(left < right)
 * { 
 *  int mid = (left+ right) / 2;
 * if mid == left == right
 * }
*/
//2022-09-30 有问题 不懂  不懂 还是不懂...
// mid永远是一半,但是又因为整除的情况
// 有这么几种情况
//              right = mid , right = mid+1
// left = mid 
// left = mid+1

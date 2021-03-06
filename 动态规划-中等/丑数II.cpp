编写一个程序找出第n个丑数
丑数是只包含质因数2，3，5的正整数
示例:

输入: n = 10
输出: 12
解释: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 是前 10 个丑数。
说明:  

1 是丑数。
n 不超过1690。
class Solution {
public:
    int nthUglyNumber(int n) {
        
        priority_queue <double,vector<double>,greater<double> > q;
        
        double answer=1;
        for (int i=1;i<n;++i)
        {
            q.push(answer*2);
            q.push(answer*3);
            q.push(answer*5);
            answer=q.top();       //虽然一个for循环压三次，但是每一个i只会跳出一次
            q.pop();              //把相同的数排出来，因为是个排序队列,相同的元素会在一块所以要去掉
            while (!q.empty() && answer==q.top())
                q.pop();
        }
        return answer;
    }
};
三指针法：因为丑数只是因数只有2,3,5的数;

所以先设置一个dp数组表示当前已经找出并排列好的丑数数组；

再3个指针：i,j,k 表示 将当前已经排好的数组元素 *2，*3，*5 所得的数组（实际上，因为所得的数字最终会加入唯一的排序数组，所以并不用真正将3个数组建立起来），

因为排序后数组*2，*3，*5得到的也是已经排序数组，接下来的目的就是从这3个虚拟数组中的头元素中取得最小那个值；（实际上并不会出现3个数组）

所以关键就是如何用这3个指针进行选择，

实际上排序并不是在加入排序数组后才整理排序，而是每次用老元素*2，*3，*5生成新元素的时候，选择最小的加入达到排序目的，这个时候指针移动就起到作用了，如下过程所示：

-----------------------------------------------------

已经排好的数组，先放进第一个丑数1:[1]

排好数组*2 ：[1]*2=2

排好数组*3 ：[1]*3=3

排好数组*5 ：[1]*5=5

选结果中最小的数加入数组，此时明显是2，新的排序数组为[1,2]；

-----------------------------------------------------

已经排好的数组:[1，2]------此时上次结果中，2，3，5只用到了2；但3明显是这次需要加入的数；既然2已经加入，再去对比2没意义了，那么就将 （*2的指针） [1]转向下一位[2]，对比 （下一个元素*2 和3，5）的大小，取最小的加入；

排好数组*2 ：[2]*2=4

排好数组*3 ：[1]*3=3

排好数组*5 ：[1]*5=5

选结果中最小的数加入数组，此时明显是2，新的排序数组为[1,2,3]；

-----------------------------------------------------

已经排好的数组:[1，2，3]------3已经加入，移动它的指针到排序数组下一位；

排好数组*2 ：[2]*2=4

排好数组*3 ：[2]*3=6

排好数组*5 ：[1]*5=5

选结果中最小的数加入数组，此时明显是4，新的排序数组为[1,2,3,4]；

依次类推；可以看到，实际上，只需将指针进行分别移动就可以了；所以要做出3个指针；

-----------------------------------------------------

维护3个值val2,val3,val5，表示将当前排列好数组 分别*2，*3，*5所得的结果数；

因为可能3组数出现重复现象，所以要判断是否重复后再加入

class Ugly {
  public int[] nums = new int[1690];
  Ugly() {
    nums[0] = 1;
    int ugly, i2 = 0, i3 = 0, i5 = 0;

    for(int i = 1; i < 1690; ++i) {
      ugly = Math.min(Math.min(nums[i2] * 2, nums[i3] * 3), nums[i5] * 5);
      nums[i] = ugly;

      if (ugly == nums[i2] * 2) ++i2;
      if (ugly == nums[i3] * 3) ++i3;
      if (ugly == nums[i5] * 5) ++i5;
    }
  }
}

class Solution {
  public static Ugly u = new Ugly();
  public int nthUglyNumber(int n) {
    return u.nums[n - 1];
  }
}

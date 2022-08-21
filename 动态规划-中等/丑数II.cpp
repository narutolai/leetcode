// 编写一个程序找出第n个丑数
// 丑数是只包含质因数2，3，5的正整数
// 示例:

// 输入: n = 10
// 输出: 12
// 解释: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 是前 10 个丑数。
// 说明:  

// 1 是丑数。
// n 不超过1690。
class Solution
{
public:
  int nthUglyNumber(int n)
  {
    //优先队列底层是用堆实现的，每次push() 和 pop() 都会调整堆，默认是大根堆
    //priority_queue<int> q;
    //这个是小根堆
    //每次pop都会把最小的数弹出来
    priority_queue<int, vector<int>, greater<int>> q;
    int answer = 1;
    for (int i = 1; i < n; ++i)
    {
      q.push(answer * 2);
      q.push(answer * 3);
      q.push(answer * 5);
      answer = q.top(); //虽然一个for循环压三次，但是每一个i只会跳出一次
      q.pop();          //把相同的数排出来，因为是个排序队列,相同的元素会在一块所以要去掉
      while (!q.empty() && answer == q.top())
        q.pop();
    }
    return answer;
  }
};

//遍历次数2
// 2  3  5
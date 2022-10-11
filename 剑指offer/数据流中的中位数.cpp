
class MedianFinder
{
public:
    priority_queue<int, vector<int>, less<int>> queMin;
    priority_queue<int, vector<int>, greater<int>> queMax;

    MedianFinder() {}

    void addNum(int num)
    {
        if (queMin.size() != queMax.size())//总数为奇数 当前数为偶数个
        {
            queMin.push(num);
            queMax.push(queMin.top());
            queMin.pop();
        }
        else
        {
            queMax.push(num);
            queMin.push(queMax.top());
            queMax.pop();
        }
    }

    double findMedian()
    {
        if (queMin.size() > queMax.size())
        {
            return queMin.top();
        }
        return (queMin.top() + queMax.top()) / 2.0;
    }
};
//阿秀的学习笔记中指出这种方法只可以用于数据可以存入到内存中的情况
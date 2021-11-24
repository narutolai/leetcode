
class Solution
{
public:
    //高效寻找素数返回区间[2,n)中有几个素数
    int countPrimes(int n)
    {
        vector<int> isPrime(n, true);

        //为什么只需要遍历到根号n呢，因为下面的j就是从i的平方开始往后累加的 ，假设i=根号n的时候 第二个循环 会把后面的数乘完。
        for (int i = 2; i * i < n; i++)
        {
            //如果这个数是素数
            if (isPrime[i])
            {
                //那么这个数的 2、3、4、5..... 倍都不是素数
                for (int j = i * i; j < n; j += i)
                    isPrime[j] = false;
            }
        }

        int count = 0;
        for (int i = 2; i < n; i++)
            if (isPrime[i])
                count++;
        return count;
    }
};
//这个算法有一个名字 叫做 埃拉托色尼筛选法
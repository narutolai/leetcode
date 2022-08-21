class Solution {
public:
    int countPrimes(int n) {
        vector<int> isPrime(n, 1);
        int ans = 0;
        for (int i = 2; i < n; ++i) {
            if (isPrime[i]) {
                ans += 1;
                if ((long long)i * i < n) {
                    for (int j = i * i; j < n; j += i) {
                        isPrime[j] = 0;
                    }
                }
            }
        }
        return ans;
    }
};

//为什么j要从i*i开始呢， 因为 i*（i-1） 会被 j=i-1的时候 给计算掉的，

class Solution
{
public:
    int countPrimes(int n)
    {
        vector<bool> isPrime(n, true);
        for (int i = 2; i * i < n; i++)
            if (isPrime[i])//如果当前数是素数
                for (int j = i * i; j < n; j += i)
                    isPrime[j] = false;//那么他的倍数就都不是素数

        int count = 0;
        for (int i = 2; i < n; i++)
            if (isPrime[i])
                count++;
        return count;
    }
};
//遍历次数2
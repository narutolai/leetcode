public int trailingZeroes(int n) {
    int count = 0;
    while (n > 0) {
        count += n / 5;
        n = n / 5;
    }
    return count;
}

原题就是说 计算一个阶乘数的末尾的连续0的个数
然后就数学分析 ：
首先是  末尾出现0 ，那么肯定是和10相乘了，也就是2*5，，，，2 的个数会比5多，，这样的话 就变成数5的个数了

那么从1遍历到n  数每一个数因子中5的个数 可得解答，但是超时了 如下：

public int trailingZeroes(int n) {
    int count = 0;
    for (int i = 1; i <= n; i++) {
        int N = i;
        while (N > 0) {
            if (N % 5 == 0) {
                count++;
                N /= 5;
            } else {
                break;
            }
        }
    }
    return count;
}

然后就继续分析 ，，，就发现，，，
每隔 5 个数，出现一个 5，每隔 25 个数，出现 2 个 5，每隔 125 个数，出现 3 个 5... 以此类推。
最终 5 的个数就是 n / 5 + n / 25 + n / 125 ...
比如 25的阶乘就是
5*5 *.....4*5......3*5.....2*5....1*5......1
 就是说每隔25个数 会多一个5，
 public int trailingZeroes(int n) {
    int count = 0;
    while (n > 0) {
        count += n / 5;
        n = n / 5;
    }
    return count;
}
  

有 n 位乘客即将登机，飞机正好有 n 个座位。第一位乘客的票丢了，他随便选了一个座位坐下。

剩下的乘客将会：

如果他们自己的座位还空着，就坐到自己的座位上，

当他们自己的座位被占用时，随机选择其他座位
第 n 位乘客坐在自己的座位上的概率是多少？

 

示例 1：

输入：n = 1
输出：1.00000
解释：第一个人只会坐在自己的位置上。
示例 2：

输入: n = 2
输出: 0.50000
解释：在第一个人选好座位坐下后，第二个人坐在自己的座位上的概率是 0.5。
因此，可得递推公式如下：

f(n) = 1 / n + (n - 2) * (1 / n) * f(n-1)
f(n)=1/n+(n−2)∗(1/n)∗f(n−1)

其中，f(n)f(n)代表有nn位乘客，且第一位乘客随机选择座位的前提下，第nn位乘客能坐到自己座位上的概率（即题目所求）。

第1种情况：第一位刚好选择了自己的位置坐下，那么他就不会影响到后续所有人的位置，而一共有nn个座位，第一位乘客随机选择座位的，因此他选择自己的位置坐下的概率是1/n1/n，同时他选择自己的位置坐下后，第nn位乘客肯定就是会坐到自己的位置上，因此在第一位乘客选择了自己座位坐下的前提下，第n为乘客选择自己座位坐下的概率为1。总的概率就是(1/n) * 1.0(1/n)∗1.0。

第2种情况：第一位乘客刚好坐到了第nn位乘客的位置。那么后面第nn位乘客就不可能坐到自己的位置上了。因此在第一位乘客坐到了第nn位乘客的位置上的前提下，第nn位乘客坐到自己位置的概率即为(1/n) * 0.0 = 0.0(1/n)∗0.0=0.0。

第3种情况：第一位乘客坐到了除自己和第nn位乘客的其它(n-2)(n−2)位乘客的位置上。这种情况稍微复杂多一点点。因为第一位乘客占了这(n-2)(n−2)位乘客中的一个位置，假设为第ii位乘客，那么第ii位乘客没法坐到自己位置上，就可能随机选一个位置坐下，这就会干扰到第nn位乘客的位置选择。但是，细细一想，其实发现是有规律的。也就是说当第一位乘客占用了除自己和第nn位乘客的其它(n-2)(n−2)位乘客的位置的时候，假设这个位置是ii，那么相当于第ii个位置（对应第ii位乘客的位置）作废了，可以从nn个位置中移除了，即剩下了n-1n−1个作为，同时我们把第ii位乘客变成了“忘记带票的第1位乘客”。然后问题就转化成了f(n-1)f(n−1)的问题。那么，这种情况的概率即为(n - 2) * (1 / n) * f(n-1)(n−2)∗(1/n)∗f(n−1)。

    public double nthPersonGetsNthSeat(int n) {
        // f(n) = 1 / n + (n - 2) * (1 / n) *  f(n-1)
        double prev = 1;
        double cur = 0;

        for (int i = 2; i <= n; i++) {
            cur = 1.0 / i + (i - 2) * (1.0 / i) * prev;
            prev = cur;
        }

        return prev;
    }


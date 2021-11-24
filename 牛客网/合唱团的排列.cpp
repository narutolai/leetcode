// 计算最少出列多少位同学，使得剩下的同学排成合唱队形

// 说明：

// N位同学站成一排，音乐老师要请其中的(N-K)位同学出列，使得剩下的K位同学排成合唱队形。
// 合唱队形是指这样的一种队形：设K位同学从左到右依次编号为1，2…，K，他们的身高分别为T1，T2，…，TK，   则他们的身高满足存在i（1<=i<=K）使得T1<T2<......<Ti-1<Ti>Ti+1>......>TK。
// 你的任务是，已知所有N位同学的身高，计算最少需要几位同学出列，可以使得剩下的同学排成合唱队形。

// 输入
// 8          a                   b
// add  : 4   4   3   5   4   2   4   5
// right: 3   3   2   3   2   1   1   1
// left:  1   1   1   2   2   1   3   4
//       186 186 150 200 160 130 197 200
// 输出
// 4
// 因为必须是凸型  我们只考虑a到b   每一个数多算了一次要加上1.

//我们需要计算每一个位置往左的最长递减子序列 以及往右的最长递增子序列 找出最的就行了
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main()
{
    int n;
    while (cin >> n)
    {
        int size = n;
        int a[n];
        for (int i = 0; i < n; i++)
            cin >> a[i];

        vector<int> left(size, 1);
        for (int i = 1; i < n; i++)
            for (int j = 0; j < i; j++)
                if (a[i] > a[j])
                    left[i] = max(left[i], left[j] + 1);

        vector<int> right(size, 1);
        for (int i = n - 2; i >= 0; i--)
            for (int j = n - 1; j > i; j--)
                if (a[i] > a[j])
                    right[i] = max(right[i], right[j] + 1);

        int min_ = 100000;
        for (int i = 1; i < n - 1; i++)
            min_ = min(n - left[i] - right[i] + 1, min_);
        cout << min_ << endl;
    }
    return 0;
}

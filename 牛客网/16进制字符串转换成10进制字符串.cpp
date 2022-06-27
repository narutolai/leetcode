#include <iostream>
#include <string>
#include <math.h>
using namespace std;
int main()
{
    string str;
    while (cin >> str)
    {
        int sum = 0;
        int size = str.size();
        for (int i = size - 1; i >= 2; i--)//为什么i>=2呢 因为 最开始的两个字符是 0x
        {
            char 
            if (str[i] >= '0' && str[i] <= '9')
            {
                sum += (str[i] - '0') * pow(16, size - i - 1);
            }
            else if (str[i] >= 'A' && str[i] <= 'F')
            {
                sum += (str[i] - 'A' + 10) * pow(16, size - i - 1);
            }
            else
            {
                sum += (str[i] - 'a' + 10) * pow(16, size - i - 1);
            }
        }
        cout << '0' + sum - 48 << endl;
    }
    return 0;
}
//遍历次数1
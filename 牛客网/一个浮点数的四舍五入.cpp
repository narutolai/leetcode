#include <iostream>
using namespace std;
int main()
{
    double x;
    cin >> x;
    int d = (int)x;
    int r = x - d >= 0.5 ? d + 1 : d;
    cout << r << endl;
    return 0;
}

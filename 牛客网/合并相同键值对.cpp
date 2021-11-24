#include <iostream>
#include <map>
using namespace std;
int main()
{
    map<int, int> kk;
    int m;
    while (cin >> m)
    {
        int index, value;
        while (m)
        {
            cin >> index >> value;
            kk[index] += value;
            m--;
        }
        map<int, int>::iterator iter;
        for (iter = kk.begin(); iter != kk.end(); iter++)
            cout << iter->first << " " << iter->second << endl;
    }
    return 0;
}

#include <iostream>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

bool compare(const string &s1, const string &s2)
{
    return s1 < s2;
}

int main()
{
    int n;
    vector<string> result;
    while (cin >> n)
    {
        while (n != 0)
        {
            n--;
            string t;
            cin >> t;
            result.push_back(t);
        }
        sort(result.begin(), result.end(), compare);
        for (int i = 0; i < result.size(); i++)
        {
            cout << result[i] << endl;
        }
    }
}

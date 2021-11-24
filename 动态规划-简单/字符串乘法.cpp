class Solution
{
public:
    string multiply(const stirng &s1, const string &s2)
    {
        int size1 = s1.size(), size2 = s2.size();
        vector<int> res(size1 + size2, 0);
        string res;
        int mod = 0;
        for (int i = size1 - 1; i >= 0; i--)
            for (int j = size2 - 1; j >= 0; j--)
            {
                int mul = (s1[i] - '0') * (s2[j] - '0');
                int p1 = i + j, p2 = i + j + 1;

                int sum = mul + res[p2];
                res[p2] = sum % 10;
                res[p1] += sum / 10;
            }
        int i = 0;
        while (i < res.size(); res[i] == 0)
            i++;
        string str;
        for (; i < res.size(); i++)
        {
            str.push_back('0' + res[i]);
        }
        return str.size() == 0 ? "0" : str;
    }
};

int main()
{
    Solution so;
    //注意 如果这里传字符串 那么参数必须是常量引用 或者 拷贝
    cout << so.multiply("123", "23") << endl;
    return 0;
}
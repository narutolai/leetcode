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
                int mul = (s1[i] - '0') * (s2[j] - '0') + res[i + j + 1];
                res[i + j + 1] = mul % 10;
                res[i + j] += mul / 10;
            }
        int i = 0;
        while (i < res.size() && res[i] == 0)
            i++;
        string str;
        for (; i < res.size(); i++)
        {
            str.push_back('0' + res[i]);
        }
        return str.size() == 0 ? "0" : str;
    }
};
//遍历次数 3
//i+j i+j+1 的问题 i+j i+j+1的问题  
int main()
{
    Solution so;
    //注意 如果这里传字符串 那么参数必须是常量引用 或者 拷贝
    cout << so.multiply("123", "23") << endl;
    return 0;
}
//我怎么想到了编码的奥秘里的与非门呢
//首先给出java版本的中心算法
class Solution
{
public:
  class Solution
{
public: //解码总数 我靠 这玩意儿有问题啊
    string longestPalindrome(string s)
    {
        int res = 0;
        int start = 0;
        int max_ = 0;
        for (int i = 0; i < s.size(); i++)
        {
            //
            int length1 = expand(s, i, i);
            int length2 = expand(s, i, i + 1);
            //获取最长的字串长度
            int max_ = max(length1, length2);

            if (max_ > res)
            {
                res = max_;
                start = i - (max_ - 1) / 2; //怎么解决奇数偶数/2的问题  发现减去一个1就可以了卧槽
            }
        }
        //起始点 和长度
        return s.substr(start, res);
    }
    int expand(string s, int left, int right)
    {
        while (left >= 0 && right < s.size() && s[left] == s[right])
        {
            left--;
            right++;
        }
        return right - left - 1;
    }
};
}
//然后下面是c++的动态规划版本的
class Solution
{
public:
    string longestPalindrome(string s)
    {
        int len = s.size();
        if (len == 0 || len == 1)
            return s;
        int start = 0;                                 //回文串起始位置
        int max = 1;                                   //回文串最大长度
        vector<vector<int>> dp(len, vector<int>(len)); //定义二维动态数组
        for (int i = 0; i < len; i++)                  //初始化状态
        {
            dp[i][i] = 1;
            if (i < len - 1 && s[i] == s[i + 1])
            {
                dp[i][i + 1] = 1;
                max = 2;
                start = i;
            }
        }
        for (int l = 3; l <= len; l++) //l表示检索的子串长度，等于3表示先检索长度为3的子串
        {
            for (int i = 0; i + l - 1 < len; i++)
            {
                int j = i + l - 1;                         //终止字符位置
                if (s[i] == s[j] && dp[i + 1][j - 1] == 1) //状态转移
                {
                    dp[i][j] = 1;
                    start = i;
                    max = l;
                }
            }
        }
        return s.substr(start, max); //获取最长回文子串
    }
};

//首先给出java版本的中心算法
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
            int length2 = expand(s, i, i + 1);//这里不会越界的吗没关系expand函数里做了判断
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


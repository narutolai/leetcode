//���ظ��ַ�����ִ�
//����һ���ַ��� �����ҳ����в������ظ��ַ�����ִ��ĳ���
//s ="abcabcbb"  ����Ϊ3
//s="bbbbbb"  ����Ϊ1
//s="pwwkew"  ����Ϊ3
class Solution
{
public:
    int Exist(string &s)
    {
        map<char, int> window;
        int res = 0;
        int left = 0;
        int right = 0;
        while (right <= s.size())
        {
            char c1 = s[right];
            window[c1]++;
            right++;
            //�������г����ظ����Ӵ�ʱ,�����С ֱ������ַ��ĳ��ִ���������1
            while (window[c1] > 1)
            {
                char c2 = s[left];
                window[c2]--;
                left++;
            }
            //ÿ�����ұ��ƶ�һ�ζ�����һ��max
            res = max(res, right - left);
        }
        return res;
    }
};
//�ҵ��ַ����е�������ĸ��λ��
//��һ���ַ���s ���ַ���p  �ҵ�s��������p����ĸ��λ�ʵ��ִ� ������Щ�ִ�����ʼλ��
//s="cbadefbac"   p="abc"
// res=[0,6] ���� cba  ����abc   bac��Ҳ��abc
class Solution
{
public:
    vector<int> Exist(string s, string t)
    {

        map<char, int> need;
        for (auto c : t)
            need[c]++;
        map<char, int> window;

        vector<int> res;
        int left = 0;
        int right = 0;
        int match = 0;

        while (right <= s.size())
        {
            char c = s[right];
            //����ַ���Ҫͳ��
            if (need[c])
            {
                window[c]++;
                if (window[c] == need[c])
                    match++; //match��
            }
            right++;
            while (match == need.size())
            {
                if (right - left == t.size())//�������ϳ���һ�� 
                {
                    res.push_back(left);
                }
                char c = s[left];
                if (need[c])
                {
                    window[c]--;
                    if (window[c] < need[c])
                        match--;
                }

                left++;
            }
        }
        return res;
    }
};
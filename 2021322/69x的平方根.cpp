class Solution
{
public:
    int mySqrt(int x)
    {
        int l = 0, r = x, ans = -1;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if ((long long)mid * mid <= x)//O(log(n)).//ȷʵ��
            {
                ans = mid;
                l = mid + 1;
            }
            else
            {
                r = mid - 1;
            }
        }
        return ans;
    }
};//����ô�����Զ���????
//�������forѭ����֪ ����ʵ�������� i---x��ƽ����֮����һ����
//��֤�����һ������ȡƽ�����԰�
class Solution
{
public:
    int mySqrt(int x)
    {
        long long y = x;
        long long i = 1;
        for (; i * i <= y; i++)//O(n)
            ;

        return i * i == y ? i : i - 1;
    }
};

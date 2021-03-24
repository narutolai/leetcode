class Solution
{
public:
    bool buddyStrings(string a, string b)
    {
        //长度不等肯定false
        if (a.size() != b.size())
            return false;

        int first_index = 0, second_index = 0;
        int i = 0;
        //ab相等
        if (a == b)
        {
            //统计是否有重复字母出现
            vector<int> count(26, 0);
            for (auto &it : a)
            {
                count[it - 'a']++;
            }
            for (auto &it : count)
                if (it > 1)
                    return true; //有就true
            return false;        //没有就false
        }
        //找第一个
        while (i < a.size() && a[i] == b[i])
            i++;
        first_index = i;
        i++;
        //找第二个
        while (i < a.size() && a[i] == b[i])
            i++;
        second_index = i;
        i++;
        //可以交互就交换 然后从下一个位置开始统计后边的是否相等
        if (a[first_index] == b[second_index] && a[second_index] == b[first_index])
        {
            for (int j = i; j < a.size(); j++)
                if (a[j] != b[j])
                    return false;
            return true;
        }
        return false;
    }
};

// 如果字符串中不含有任何 'aaa'，'bbb' 或 'ccc' 这样的字符串作为子串，那么该字符串就是一个「快乐字符串」。

// 给你三个整数 a，b ，c，请你返回 任意一个 满足下列全部条件的字符串 s：

// s 是一个尽可能长的快乐字符串。
// s 中 最多 有a 个字母 'a'、b 个字母 'b'、c 个字母 'c' 。
// s 中只含有 'a'、'b' 、'c' 三种字母。
// 如果不存在这样的字符串 s ，请返回一个空字符串 ""。

//  

// 示例 1：

// 输入：a = 1, b = 1, c = 7
// 输出："ccaccbcc"
// 解释："ccbccacc" 也是一种正确答案。
// 示例 2：

// 输入：a = 2, b = 2, c = 1
// 输出："aabbc"
// 示例 3：
class Solution
{
public:
    string longestDiverseString(int a, int b, int c)
    {
        string ans;
        vector<pair<int, char>> m{{a, 'a'}, {b, 'b'}, {c, 'c'}};
        while (1)
        {
            //每选一次都会排序
            sort(rbegin(m), rend(m));
            int pre_size = ans.size();
            //先选最大的数就可以了
            for (auto &[cnt, c] : m)
            {
                //如果该字母剩余数量为0或者该字符与字符串ans的最后两个字符相等，就不能再添加该字母了 不然会出现3个重复的字符
                if (cnt == 0 || ans.size() >= 2 && c == ans.back() && c == ans[ans.size() - 2])
                    continue;
                ans += c;
                cnt--;
                break;
            }
            //如果尺寸不变说明没得选了。
            if (pre_size == ans.size())
                break;
        }
        return ans;
    }
};
//遍历次数2
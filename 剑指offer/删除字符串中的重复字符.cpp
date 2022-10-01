// 给出由小写字母组成的字符串 S，重复项删除操作会选择两个相邻且相同的字母，并删除它们。

// 在 S 上反复执行重复项删除操作，直到无法继续删除。

// 在完成所有重复项删除操作后返回最终的字符串。答案保证唯一。
//  
// 示例：

// 输入："abbaca"
// 输出："ca"
// 解释：
// 例如，在 "abbaca" 中，我们可以删除 "bb" 由于两字母相邻且相同，这是此时唯一可以执行删除操作的重复项。之后我们得到字符串 "aaca"，其中又只有 "aa" 可以执行重复项删除操作，
//所以最后的字符串为 "ca"。
class Solution
{
public:
    string removeDuplicates(string S)//真是太妙了。
    {
        string stk;
        for (char ch : S)
        {
            if (!stk.empty() && stk.back() == ch)
            {
                stk.pop_back();
            }
            else
            {
                stk.push_back(ch);//abbaca 
            }
        }
        return stk;
    }
};
//遍历次数 1
//不过这个题还是很妙的
//注意这个题是消消乐。
//2022/09/30 21:22
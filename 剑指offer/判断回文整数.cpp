// 给你一个整数 x ，如果 x 是一个回文整数，返回 ture ；否则，返回 false 。

// 回文数是指正序（从左向右）和倒序（从右向左）读都是一样的整数。例如，121 是回文，而 123 不是。

//  

// 示例 1：

// 输入：x = 121
// 输出：true
// 示例 2：

// 输入：x = -121
// 输出：false
// 解释：从左向右读, 为 -121 。 从右向左读, 为 121- 。因此它不是一个回文数。
// 示例 3：

// 输入：x = 10
// 输出：false
// 解释：从右向左读, 为 01 。因此它不是一个回文数。
// 示例 4：

// 输入：x = -101
// 输出：false
//  
class Solution
{
public:
    bool isPalindrome(int x)
    {
        if (x < 0)
            return false;
        else
        {
            int x_ = x;
            long long result = 0, mod = 0;
            while (x)
            {
                mod = x % 10;
                x /= 10;
                result = result * 10 + mod;
            }
            return result == x_;
        }
        //要不直接to_string()算了。
        //其实算到一半就行了 ，不需要除尽的
    }
};
//遍历次数 2
//其实感觉这个方法也可以 直接再计算一遍
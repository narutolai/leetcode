#include <vector>
#include <iostream>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
};
class Solution
{
public:
    ListNode *left;
    bool traverse(ListNode *right)
    {
        if (right == nullptr)
            return true;
        bool res = traverse(right->next);
    
        res = res & (right->val == left->val);
        left = left->next;
        return res;
    }
    bool isPalindrome(ListNode *head)
    {
        left = head;
        return traverse(head);
    }
};

//遍历次数2
//从今天开始不允许自己大键盘发出声音
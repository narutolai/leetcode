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


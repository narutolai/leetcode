//删除有序链表中的重复元素，使得其只出现一次

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution
{
public:
    ListNode *deleteDuplicates(ListNode *head)
    {
        ListNode *cur = head;
        ListNode *pre = nullptr;
        head = nullptr;
        while (cur != nullptr)
        {
            if (pre == nullptr ? 1 : pre->val != cur->val)
            {
                if (pre == nullptr)
                {
                    pre = cur;
                    head = cur;
                }
                else
                {
                    pre->next = cur;
                    pre = cur;
                }
            }
            cur = cur->next;
        }
        if (pre != nullptr)
            pre->next = nullptr;
        return head;
    }
};

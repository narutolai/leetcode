/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

//迭代
class Solution
{
public:
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
    {

        ListNode *head = new ListNode(-1);
        ListNode *pivot = head;
        while (l1 && l2)
        {
            if (l1->val <= l2->val)
            {
                pivot->next = l1;
                l1 = l1->next;
            }
            else
            {
                pivot->next = l2;
                l2 = l2->next;
            }
            pivot = pivot->next;
        }
        pivot->next = l1 == NULL ? l2 : l1;
        return head->next;
    }
};

//递归
class Solution
{
public:
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
    {
        if (l1 == nullptr)
        {
            return l2;
        }
        else if (l2 == nullptr)
        {
            return l1;
        }
        else if (l1->val < l2->val)
        {
            l1->next = mergeTwoLists(l1->next, l2);
            return l1;
        }
        else
        {
            l2->next = mergeTwoLists(l1, l2->next);
            return l2;
        }
    }
};
//遍历次数 2
//合并两个有序链表 可以有迭代法何递归法

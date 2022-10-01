/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution
{
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
    {

        ListNode *p1 = headA, *p2 = headB;
        while (p1 != p2)
        {
            if (p1)
                p1 = p1->next;
            else
                p1 = headB;

            if (p2)
                p2 = p2->next;
            else
                p2 = headA;
        }
        return p1;
    }
};

//遍历次数 2
//真的是妙啊 妙啊
//我们会相遇 说明什么 说明我们走的路程一样
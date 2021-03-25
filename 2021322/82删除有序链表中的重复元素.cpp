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
//如果不满足 i-1!=i!=i+1; 就可以把i连入
class Solution
{
public:
    ListNode *deleteDuplicates(ListNode *head)
    {
        ListNode *pre = nullptr;
        ListNode *cur = head;
        head=nullptr;
        ListNode *Link = nullptr;
        while (cur != nullptr)
        {
           
            if (((pre == nullptr) ? 1 : (pre->val != cur->val)) && ((cur->next == nullptr) ? 1 : (cur->val != cur->next->val)))
            {
                if (Link == nullptr)
                {
                    Link = cur;
                    head = Link;
                }
                else
                {
                    Link->next = cur;
                    Link = cur;
                }
              
            } 
            pre = cur;
            cur = cur->next;
        }
        if(Link!=nullptr)
        Link->next=nullptr;
        return head;
    }
};

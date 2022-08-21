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
        head = nullptr;
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
        if (Link != nullptr)
            Link->next = nullptr;
        return head;
    }
};

//这里贴下递归的
class Solution
{
public:
    ListNode *deleteDuplicates(ListNode *head)
    {
        if (!head || !head->next)
        {
            return head;
        }
        if (head->val != head->next->val)
        {
            head->next = deleteDuplicates(head->next);
        }
        else
        {
            ListNode *move = head->next;
            while (move && head->val == move->val)
            {
                move = move->next;
            }
            return deleteDuplicates(move);
        }
        return head;
    }
};
//遍历次数 2
//注意是有序链表的重复元素 有序 有序 有序!!!
//此题妙啊 直接看递归的吧
//看这个写法 应该是删除元素保留一个,就是会保留一个元素的。
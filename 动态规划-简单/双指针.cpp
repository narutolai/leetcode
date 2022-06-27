struct ListNode
{
    int val;
    ListNode *next;
};
class Solution
{
public:
    //双指针之判断链表的中点
    ListNode *midnode(ListNode *head)
    {
        ListNode *fast, *slow;
        slow = fast = head;
        while (fast != nullptr && fast->next != nullptr)
        {
            fast = fast->next->next;
            slow = slow->next;
        }
        return slow;
    }

    //寻找链表的倒数第K个节点
    ListNode *reciProcalK(ListNode *head, int K)
    {
        //快指针先走K步  然后慢指针开始走就可以了
        ListNode *slow, *fast;
        fast = slow = head;
        while (K-- && fast != nullptr)
        {
            fast = fast->next;
        }
        while (fast)
        {
            fast = fast->next;
            slow = slow->next;
        }
        return slow;
    }
    //双指针之链表判环
    bool hasCycle(ListNode *head)
    {
        ListNode *fast, *slow;
        fast = slow = head;
        while (fast != nullptr && fast->next != nullptr)
        {
            fast = fast->next->next;
            slow = slow->next;

            if (fast == slow)
                return true;
        }
        return false;
    }
    //已知链表有环  返回环的起始位置
    //为什么这样就一定会相遇
    ListNode *detectCycle(ListNode *head)
    {
        ListNode *fast, *slow;
        fast = slow = head;
        while (fast != nullptr && fast->next != nullptr)
        {
            fast = fast->next->next;
            slow = slow->next;

            if (slow == fast) 
                break;
        }
        //相遇时让满指针回到起点 然后当快慢相遇时 就是环的起点
        slow = head;
        while (slow != fast)
        {
            fast = fast->next;
            slow = slow->next;
        }
        return slow;
    }
};
//遍历次数 1
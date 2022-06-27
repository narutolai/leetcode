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
            if (pre == nullptr ? true : pre->val != cur->val)
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
    //错误的递归写法
    ListNode *deleteDuplicates(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;
     
        if (head->val == head->next->val)
        {
            ListNode *cur = head->next;
            while (cur->val == head->val && cur != nullptr)
                cur = cur->next;
            head->next = cur;

            cur->next = deleteDuplicates(cur->next);
        }
        else
        {
            head->next = deleteDuplicates(head->next);//
        }
        return head;
    }
    //正确的递归写法
    ListNode *deleteDuplicates(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;
     
        if (head->val == head->next->val)
        {
            ListNode *cur = head->next;
            while (cur->val == head->val && cur != nullptr)
            {  
                  cur = cur->next;
            }
            return  deleteDuplicates(cur);
        }
        else
        {
            head->next = deleteDuplicates(head->next);//
        }
        return head;
    }
};
//当指针作为左值，它需要被填充， 
//好像这个有个递归的方法
//竟然写错了 看来还是有点不理解递归函数
//递归函数，当前节点的下一个节点应该是什么呢，
//反正下一个节点的值不能和当前节点的值相等
//反正我就相信你会返回正确的下一个节点，剩下的我什么都不用管，
//只要甩出 head->next=  就可以，反正就是相信你可以返回正确的下一个节点。
//怎么理解链表中的递归，把head想成倒数倒数第二个节点。
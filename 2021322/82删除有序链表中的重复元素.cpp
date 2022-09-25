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
        if (!head || !head->next)//为什么这里还要判断head->next,因为下面有使用到呀
        {
            return head;
        }
        if (head->val != head->next->val)
        {
            head->next = deleteDuplicates(head->next);
        }
        else
        {
            ListNode *pstSameValueNode = head->next;
            while (pstSameValueNode && head->val == pstSameValueNode->val)
            {
                pstSameValueNode = pstSameValueNode->next;
            }
            return deleteDuplicates(pstSameValueNode);
        }
        return head;
    }
};
//我觉得写递归函数 要明确 参数是什么返回值是什么，然后剩下的就交给递归了 和 写动态规划方程一样要有整体思维,
//比如针对ListNode *deleteDuplicates(ListNode *head)函数,这个函数的参数是一个链表头节点,然后可以返回一个没有重复元素的链表
//
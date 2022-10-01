/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
//这个head是第一个节点不是头节点。 不带头节点的。
class Solution
{
public:
    ListNode *deleteNode(ListNode *head, int val)//把链表中值为val的都删掉
    {
        //初始化的时候就要定义当前和下一个。
        ListNode *cur = head;
        ListNode *next = cur->next;
        if (cur->val == val)
            return next;

        while (next != NULL)
        {
            if (next->val == val)
            {
                cur->next = next->next; //
            }
            else
            {
                cur = next;
            }
            next = next->next;
        }
        return head;
    }
    //删除链表中的一个值 有相同的都删掉 1 2 2 3 4 2 2 6;
    //递归法 没问题 亲测没问题,,,似乎掌握了一点点诀窍....
    ListNode* deleteNode(ListNode*head, int val)
    {
        if(head == nullptr)
        return nullptr;

        if(head->val == val)
        {
            return deleteNode(head->next, val);
        }
        
        head->next = deleteNode(head->next, val);
        return head;
    }

};
//遍历次数 1
// 直接用递归做试试

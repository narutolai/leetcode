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
//将旋转链表每一个节点向右移动k个位置
class Solution
{
public:
    ListNode *rotateRight(ListNode *head, int k)
    {
        ListNode *cur = head;
        if (cur == nullptr)
            return 0;
      //首先我们统计出所有的节点个数
        int count = 1;
        while (cur->next != nullptr)
        {
            count++;
            cur = cur->next;
        }
      //如果移动次数是所有节点的整数倍 就直接返回头节点了，等于没有动
        if (k % count == 0)
            return head;
        
        //退出时 cur为最后一个节点
        //先让单链表成环状链表，即尾部节点的下一个节点指向头节点。    
        cur->next = head;

        //  然后 我们要计算一个偏移量offset，这个偏移量就是一个对应关系
        //  比如说 对于   1 2 3 4 5
        //  如果 k=1   5 1 2 3 4   那么链表最终尾节点就是4
        //  如果k =2     4 5 1 2 3   那么链表最终尾部节点就是3   
        int offset = count - k % count - 1;
        //计算出偏移量后确定尾节点
        //当然这里为了得出尾节点，使用快慢指针也是可行的
        cur = head;
        while (offset)
        {
            offset--;
            cur = cur->next;
        }
        //尾节点的下一个节点就是头节点
        ListNode *newhead = cur->next;
        //然后再置尾部节点的下一个节点是nullptr 不然会成循环链
        cur->next = nullptr;
        return newhead;
    }
};

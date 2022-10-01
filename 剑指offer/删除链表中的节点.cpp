class Solution
{
public:
//迭代法
    ListNode *removeZeroSumSublists(ListNode *head)
    {
        ListNode *dummy_head = new ListNode(0, head); //虚拟头结点，内值为0，防止一整个链表和为0的情况
        unordered_map<int, ListNode *> hashMap;
        int curSum = 0;
        for (ListNode *p = dummy_head; p != nullptr; p = p->next)
        { //哈希表记录前缀和
            curSum += p->val;
            hashMap[curSum] = p;
        }
        curSum = 0;
        for (ListNode *p = dummy_head; p != nullptr; p = p->next)
        { //差额数组算法
            curSum += p->val;
            p->next = hashMap[curSum]->next;
        }
        return dummy_head->next;
    }
    //递归法 这个递归法也不错
    ListNode *removeZeroSumSublists(ListNode *head)
    {
        if (head == NULL)
            return NULL;
        int sum = 0;
        for (ListNode *cursor = head; cursor != NULL; cursor = cursor->next)
        {
            sum += cursor.val;
            if (sum == 0)
            {
                return removeZeroSumSublists(cursor->next);
            }
        }
        head->next = removeZeroSumSublists(head->next);
        return head;
    }
};
//删除链表中连续节点和为0的节点,直到最后没有为0的
// 2022/09/30 这种链表的递归解法,,,,我看了后还是有点启发的,
// 
// 假如不是链表 是数组 ,你又会怎么做呢,,,想想 计算机中其实无非就两种 一种是数组 一种是链表,,,
// 算法还是有点用的...
//遍历次数 1
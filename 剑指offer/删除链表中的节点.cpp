class Solution
{
public:
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
    ListNode* removeZeroSumSublists(ListNode *head)
    {
        if (head == null)
            return null;
        int sum = 0;
        for (ListNode cursor = head; cursor != null; cursor = cursor.next)
            if ((sum += cursor.val) == 0)
                return removeZeroSumSublists(cursor.next);
        head.next = removeZeroSumSublists(head.next);
        return head;
    }

} int main()
{

    std::vector<int> vecnum = {1, 2, 3, -3, 1, -1, 4};
    ListNode *head = new ListNode;
    ListNode *cur = head;
    for (int i = 0; i < vecnum.size(); ++i)
    {
        cur->next = new ListNode;
        cur->next->val = vecnum[i];
        cur->next->next = nullptr;
        cur = cur->next;
    }

    return 0;
}
//删除链表中连续节点和为0的节点,直到最后没有为0的
//遍历次数 1
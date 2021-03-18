
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr){};
    ListNode(int x) : val(x), next(nullptr){};
    ListNode(int x, ListNode *next) : val(x), next(next){};
};
void outitem(ListNode *pivot)
{
    while (pivot != nullptr)
    {
        cout << pivot->val << endl;
        pivot = pivot->next;
    }
}

class Solution
{
public:
    ListNode *Head;
    //递归方式返回整个链表
    ListNode *reverse(ListNode *head)
    {
        if (head->next == nullptr)
        {
            Head = head;
            return head;
        }

        ListNode *temp = reverse(head->next);
        temp->next = head;
        return head;
    }

    ListNode *reverseBetween(ListNode *head, int left, int right)
    {
        ListNode *head_ = new ListNode();
        head_->next = head;

        ListNode *left_pre = head_;
        int i = 0;
        while ((i + 1) != left)
        {
            left_pre = left_pre->next;
            i++;
        }
        ListNode *right_p = left_pre;
        while (i != right)
        {
            right_p = right_p->next;
            i++;
        }

        ListNode *right_af = right_p->next;
        ListNode *pre = right_p->next;
        ListNode *cur = left_pre->next;
        ListNode *nex = cur == nullptr ? nullptr : cur->next;

        while (cur != right_af)
        {
            cur->next = pre;
            pre = cur;
            cur = nex;
            nex = (nex == nullptr) ? nex : nex->next;
        }
        left_pre->next = pre;
        return head_->next;
    }
};

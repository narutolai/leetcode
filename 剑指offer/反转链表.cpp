
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

class Solution
{
public: //反转整个链表
    ListNode *successor;
    ListNode *reverse(ListNode *head)
    {
        //如果到了最后一个节点 直接返回
        if (head->next == nullptr)
            return head;
        ListNode * newhead = reverse(head->next);
        head->next->next = head;
        head->next = nullptr;
        return newhead;
    }
    //反转前n个链表
    ListNode *reverseN(ListNode *head, int n)
    {
        if (n == 1)
        {
            //后继者的位置
            successor = head->next;
            return head;
        }
        ListNode *newhead = reverseN(head->next, n - 1); //3 2  1
        head->next->next = head;
        head->next = successor;
        return newhead;
    }
    //反转m--n中间的节点
    ListNode *reverseBetween(ListNode *head, int m, int n)
    {
        if (m == 1) //假设索引从1开始的啊
            return reverseN(head, n);
        head->next = reverseBetween(head->next, m - 1, n - 1);
        return head;
    }
    //k个一组反转链表  1-->2-->3-->4-->5-->6-->7
    ListNode *reverseKGroup(ListNode *head, int k) //2->1   4->3  6->5
    {
        if (head == nullptr)
            return nullptr;
        ListNode *temp = head;
        for (int i = 0; i < k; i++)
        {
            //不够k个
            if (temp == nullptr)
                return head;
            temp = temp->next;
        }

        ListNode *newhead = reverse(head, temp);
        
        head->next = reverseKGroup(temp, k);
        return newhead;
    }

    //反转st和et之间的元素左闭右边开
    ListNode *reverse(ListNode *st, ListNode *et)
    {
        if (st->next == et)
        {
            return st;
        }
        ListNode *newhead = reverse(st->next, et);
        st->next->next = st->next;
        st->next = et;
        return newhead;
    }
    //迭代法实现
    ListNode *reverse(ListNode *st, ListNode *et)
    {
        ListNode *pre, *cur, *next;
        pre = nullptr, cur = st, next = st;
        while (cur != et)
        {
            next = cur->next;

            cur->next->next = cur;
            cur->next = pre;

            pre = cur;
            cur = next;
        }
        return cur;
    }
};

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
public: //反转整个链表
    ListNode *successor;
    //1-->2-->3-->4     倒数第2个调用栈
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
//遍历次数 2
//1.反转链表 直接返回newhead
//2.反转链表前n个节点 需要后继者参数
//3.反转链表的m--n个节点 需要借助2。
//4.反转两个节点间的节点,左闭右开。
//5.K个一组反转链表，需要借助4. k个一组反转链表可以多看看
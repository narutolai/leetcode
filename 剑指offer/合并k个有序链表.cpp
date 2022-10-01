class Solution
{
public:
    ListNode *mergeTwoLists(ListNode *a, ListNode *b)
    {
        if ((!a) || (!b))
            return a ? a : b;
        ListNode head, *tail = &head, *aPtr = a, *bPtr = b;
        while (aPtr && bPtr)
        {
            if (aPtr->val < bPtr->val)
            {
                tail->next = aPtr;
                aPtr = aPtr->next;
            }
            else
            {
                tail->next = bPtr;
                bPtr = bPtr->next;
            }
            tail = tail->next;
        }
        tail->next = (aPtr ? aPtr : bPtr);
        return head.next;
    }

    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        ListNode *ans = nullptr;
        for (size_t i = 0; i < lists.size(); ++i)
        {
            ans = mergeTwoLists(ans, lists[i]);
        }
        return ans;
    }
};

//分治合并
class Solution
{
public:
    ListNode *mergeTwoLists(ListNode *a, ListNode *b)
    {
        if ((!a) || (!b))
            return a ? a : b;
        ListNode head, *tail = &head, *aPtr = a, *bPtr = b;
        while (aPtr && bPtr)
        {
            if (aPtr->val < bPtr->val)
            {
                tail->next = aPtr;
                aPtr = aPtr->next;
            }
            else
            {
                tail->next = bPtr;
                bPtr = bPtr->next;
            }
            tail = tail->next;
        }
        tail->next = (aPtr ? aPtr : bPtr);
        return head.next;
    }

    ListNode *merge(vector<ListNode *> &lists, int l, int r)
    {
        if (l == r)
            return lists[l];
        if (l > r)
            return nullptr;
        int mid = (l + r) >> 1;
        ListNode *left = merge(lists, l, mid);
        ListNode *right = merge(lists, mid + 1, r);
        return mergeTwoLists(left, right);
    }

    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        return merge(lists, 0, lists.size() - 1);
    }
};
//优先队列
class Solution
{
public:
    struct Status
    {
        int val;
        ListNode *ptr;
        //该结构体重载该函数即可
        bool operator<(const Status &rhs) const
        {
            return val > rhs.val; //那这里就是大于
        }
    };

    priority_queue<Status> q;

    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        for (auto node : lists)
        {
            if (node)
                q.push({node->val, node});//可以直接这样构造这个Status先向队列中压入每一个链表的头元素
        }
        ListNode head, *tail = &head;
        while (!q.empty())
        {
            auto f = q.top();//如果是要弹出最小值
            q.pop();
            tail->next = f.ptr;
            tail = tail->next;
            if (f.ptr->next)
                q.push({f.ptr->next->val, f.ptr->next});//每次push的时候都在调整堆 所以这个东西的时间复杂度就是nlogn
        }
        return head.next;
    }
};
//遍历次数 2
//话不多说直接用优先队列，但是优先队列是怎么用的很关键。算法还是其次。重载运算符注意
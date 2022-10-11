
#include <iostream>
#include <map>
using namespace std;

// LRU算法 数据结构的核心是哈希链表
struct ListNode
{
    int key, val;
    ListNode *next;
    ListNode *prev;
    ListNode() : key(0), val(0), next(nullptr), prev(nullptr) {}
    ListNode(int k, int v) : key(k), val(v), next(nullptr), prev(nullptr) {}
    ~ListNode()
    {
        cout << "delete ListNode" << endl;
    }
};
typedef struct ListNode ListNode;

//双端链表
class DoubleList
{
public:
    DoubleList() : mSize(0), mHead(new ListNode()), mTail(new ListNode())
    {
        mHead->prev = nullptr;
        mHead->next = mTail;

        mTail->prev = mHead;
        mTail->next = nullptr;
    }
    //将一个节点添加到链表头
    void addFirst(ListNode *x)
    {
        //首个元素添加
        if (mHead->next == mTail)
        {
            mHead->next = x;
            x->next = mTail;

            mTail->prev = x;
            x->prev = mHead;
        }
        else
        {
            ListNode *fisrt = mHead->next;
            mHead->next = x;
            x->next = fisrt;

            fisrt->prev = x;
            x->prev = mHead;
        }
        //节点个数加1
        mSize++;
    }
    // 这么写太危险了吧前提是 x一定存在
    // 移除一个指定的节点
    void remove(ListNode *x)
    {
        x->prev->next = x->next;
        x->next->prev = x->prev;

        x->next = nullptr;
        x->prev = nullptr;
        mSize--;
    }
    //返回移除的节点 如果移除失败 返回nullptr
    ListNode *removeLast()
    {
        if (mTail->prev != mHead)
        {
            ListNode *last = mTail->prev;
            last->prev->next = mTail;
            mTail->prev = last->prev;

            last->next = nullptr;
            last->prev = nullptr;
            mSize--;
            return last;
        }
        return nullptr;
    }
    int size() { return mSize; }
    void ShowInfo()
    {
        ListNode *pCur = mHead->next;
        for (; pCur != mTail; pCur = pCur->next)
        {
            cout << pCur->key << " " << pCur->val << " ";
        }
        cout << endl;
    }
    ~DoubleList()
    {
        cout << "delete head and tail" << endl;
        delete mHead;
        delete mTail;
    }

private:
    ListNode *mHead; //表头指针。
    ListNode *mTail; //表尾指针
    int mSize;       //当前链表中的节点个数
};
// LRUCache
class LRUCache
{
private:
    map<int, ListNode *> mKey2NodeMap;
    DoubleList mCache;
    int mCap;
    bool full()
    {
        return mCap == mCache.size();
    }

public:
    LRUCache(int capacity) : mCap(capacity) {}
    ~LRUCache()
    {
        cout << "delete cachenode" << endl;
        for (auto iter = mKey2NodeMap.begin(); iter != mKey2NodeMap.end(); iter++)
        {
            delete iter->second;
        }
    }

    //根据key值找到节点 用于Cache  什么是访问 读取是访问 写回也是访问。
    int read(int key)
    {
        //没有该节点
        if (mKey2NodeMap.count(key) != 1)
            return -1;
        //获取改节点命中节点
        ListNode *pNode = mKey2NodeMap[key];
        mCache.remove(pNode);
        mCache.addFirst(pNode);
        return pNode->val;
    }

    //最近使用过的要放在最前边
    void write(int key, int value)
    {
        //没有该节点
        if (mKey2NodeMap.count(key) != 1)
        {
            if (full())
            {
                cout << "Capicity is full" << endl;
                ListNode *pLastNode = mCache.removeLast();
                mKey2NodeMap.erase(pLastNode->key);
            }
            //新造一个节点更新链表 更新图 链表和图同时更新记得
            ListNode *pNode = new ListNode(key, value);
            mCache.addFirst(pNode);
            mKey2NodeMap[key] = pNode;
        }
        else
        {
            ListNode *pNode = mKey2NodeMap[key];
            pNode->val = value;
            mCache.remove(pNode);
            mCache.addFirst(pNode);
        }
    }

    void ShowLog()
    {
        for (auto item : mKey2NodeMap)
        {
            cout << item.first << " ";
        }
        cout << endl;
        mCache.ShowInfo();
    }
};

int main()
{
    {
        LRUCache LruCache(4);

        LruCache.write(1, 10);
        LruCache.ShowLog();

        LruCache.write(2, 20);
        LruCache.ShowLog();

        LruCache.write(3, 50);
        LruCache.ShowLog();

        LruCache.write(4, 30);
        LruCache.ShowLog();

        LruCache.write(6, 60);
        LruCache.ShowLog();
    }

    return 0;
}

/**
 *  LRU是由map<int, node*> + 双端链表组成的 注意是map是存node*啊 有一份数据就可以了 
 *  mysql的buffer 的LRU也是这样的.
 *  使用map是因为可以判断是否存在key.然后双端链表要提供将节点添加到表头的方法
*
*/

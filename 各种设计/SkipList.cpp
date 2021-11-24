//https://www.jianshu.com/p/9d8296562806

struct skiplistNode
{
    //层数深度是随机生成的。
    struct skiplistLevel
    {
        //前进指针
        struct skiplistNode *forward;
        //跨度
        unsigned int span;
        skiplistLevel() : span(0), forward(nullptr){};

    } level[];

    //后退指针
    struct skiplistNode *backward;

    int key;
    int value;

    skiplistNode(int key_,int value_,int depth):key(key_)
    skiplistNode(int depth) : key(-1), value(-1), backward(nullptr), level(new skiplistLevel[depth]){};
}

class SkipList
{
public:
    SkipList() {}
    ~SkipList() {}

    //跳跃表的增删改
    void skquery(int key) {}
    void skupdate() {}
    void skdelete(int key) {}
    void skadd(int key) {}

    //表头 表尾....省略

private:
    //表头节点 表尾节点
    struct skiplistNode *head, *tail;
    //表中节点的数量
    unsigned long length;
    //表中层数最大节点的层数
    int level;

};

int main()
{
    return 0;
}
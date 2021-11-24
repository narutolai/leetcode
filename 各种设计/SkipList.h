#ifndef _SKIPLIST_H_
#define _SKIPLIST_H_

/*
 * @DonZ
 * @Desc: compareFun(obj1, obj2), 结果如果为负，那么obj1更靠近header，obj2更靠近tail
 *      rslGetRank函数获取一个obj在跳表中的位置————header是第0个。
 *      header中的obj是不指向任何值的，但tail的obj是可能有值的 
 */

typedef int (*skipCompare)(const void* left,const void *right);

struct rskiplistNode;

struct rskiplistLevel
{
    rskiplistNode *forward;
    unsigned int span;
};

/* ZSETs use a specialized version of Skiplists */
struct rskiplistNode
{
    void *obj;
    rskiplistNode *backward;
    rskiplistLevel level[1];
};

struct rskiplist
{
    rskiplistNode *header, *tail;
    unsigned long length;
    int level;
    skipCompare compareFun;
    int m_ud;
};

rskiplist *rslCreate(skipCompare compareFun);
rskiplistNode *rslInsert(rskiplist *zsl,void *obj);
int rslDelete(rskiplist *zsl,void *obj);
unsigned long rslGetRank(rskiplist *zsl,void *obj);
void rslFree(rskiplist *zsl);

#endif

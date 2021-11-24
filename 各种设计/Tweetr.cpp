#include <iostream>
#include <map>
#include <list>
#include <queue>
#include <set>
using namespace std;

//推文/动态
struct Tweet
{
    int m_time;
    int m_Id;
    Tweet *next;
    Tweet() : m_Id(-1), m_time(0), next(nullptr) {}
    Tweet(int id, int time) : m_Id(id), m_time(time), next(nullptr) {}
    bool operator<(const Tweet &rhs)
    {
        return m_time < rhs.m_time;
    }
};

static int timeStap = 1000;
//用户
class User
{
private:
    int m_UserId;           //用户id
    set<int> mfollowedUser; //关注用户
    Tweet *head;            //推文头节点
    map<int, Tweet *> mid2Tweet;

public:
    User(int x) : m_UserId(x), head(new Tweet())
    {
        follow(m_UserId); //关注下自己
    };                    //如果这里不new而是nullptr那么
    ~User()
    {

        delete head;
        for (auto &item : mid2Tweet)
        {
            delete item.second;
        }
    }
    void follow(int UserId)
    {
        mfollowedUser.insert(UserId);
    }
    void unfollow(int UserId)
    {
        if (UserId == m_UserId)
            return;
        mfollowedUser.erase(UserId);
    }
    //发一条推文
    void post(int TweetId)
    {

        Tweet *pTweet = new Tweet(TweetId, timeStap);
        timeStap++;
        //采用头插法
        pTweet->next = head->next;
        head->next = pTweet;
        mid2Tweet[TweetId] = pTweet;
    }
    //可以这么直接返回吗
    const Tweet *getTweHead()
    {
        return head;
    }
    const set<int> &getfollower()
    {
        return mfollowedUser;
    }

    //展示用户以及用户tweet信息
    void ShowLog()
    {
        Tweet *cur = head->next;
        cout << "user id:" << m_UserId << endl;
        while (cur != nullptr)
        {
            cout << cur->m_Id << "   " << cur->m_time << " ";
            cur = cur->next;
        }
        cout << endl;
    }
};

class Twitter
{
private:
    //一个用户id 和用户的映射
    map<int, User *> mUserMap;

public:
    ~Twitter()
    {
        for (auto &item : mUserMap)
        {
            delete item.second;
        }
    }
    //某一个用户发表一条推特
    void postTweet(int userId, int tweetId)
    {
        if (mUserMap.count(userId) != 1)
        {
            mUserMap[userId] = new User(userId);
        }
        mUserMap[userId]->post(tweetId);
    }

    //follo id不存在则新建
    void follow(int followerId, int followeeId)
    {
        if (mUserMap.count(followerId) != 1)
        {
            mUserMap[followerId] = new User(followerId);
        }

        if (mUserMap.count(followeeId) != 1)
        {
            mUserMap[followeeId] = new User(followeeId);
        }

        //关注
        mUserMap[followerId]->follow(followeeId);
    }
    //取关 如果不存在则新建立
    void unfollow(int followerId, int followeeId)
    {
        if (mUserMap.count(followerId) == 1)
        {
            mUserMap[followerId]->unfollow(followeeId);
        }
    }

    //一个用户获取其前10的推特 k个链表排序 使用优先队列吧
    //这个优先队列总是不能正常的排序 ，运行会出错 但是调试的时候就不会。
    list<int> getNewsFeedTopK(int userId, int topK)
    {
        //获取当前用户的关注者 引用是别名，如果不用引用 可能会调用拷贝赋值函数
        const set<int> &user = mUserMap[userId]->getfollower();

        //有问题啊
        priority_queue<Tweet *> poriorityq;

        //先将所有链表的头节点插入到优先队列中
        for (auto item : user)
        {
            Tweet *ptw = mUserMap[item]->getTweHead()->next;
            cout << "usrid:" << item << "  twehead id  " << ptw->m_Id << endl;
            if (ptw)
                poriorityq.push(ptw);
        }
        //返回一个list的拷贝 真的是亏

        list<int> templist;
        while (!poriorityq.empty())
        {
            if (templist.size() == topK)
                break;
            auto p = poriorityq.top();
            poriorityq.pop();
            //压入tweete的id
            templist.push_back(p->m_Id);
            if (p->next)
            {
                poriorityq.push(p->next);
            }
        }
        return templist;
    }

    void ShowNewFeedTopK(int userId, int topK)
    {
        cout << "topK feed  userid :" << userId << endl;
        list<int> result = getNewsFeedTopK(userId, topK);
        for (auto ite : result)
            cout << ite << " ";
        cout << endl;
    }
    void ShowLog()
    {
        for (auto &item : mUserMap)
        {
            item.second->ShowLog();
        }
    }
};

int main()
{
    {
        Twitter twi;

        //首先创建6个用户 然后他们互相关注
        for (int j = 1; j <= 6; j++)
            for (int i = 1; i <= 6; i++)
                twi.follow(j, i);
        //然后每一个人都发一条推文
        for (int i = 1; i <= 6; i++)
            twi.postTweet(i, i);
        //展示每一个人的topk流
        for (int i = 1; i <= 6; i++)
            twi.ShowNewFeedTopK(i, 5);
        twi.ShowLog();
        cout << "========================================" << endl;
        //用户1又发了一条推文
        twi.postTweet(1, 11);
        twi.postTweet(3, 31);
        twi.postTweet(5, 51);
        for (int i = 1; i <= 6; i++)
            twi.ShowNewFeedTopK(i, 5);
        twi.ShowLog();
    }

  
    cout << "normal exist" << endl;
    return 0;
}
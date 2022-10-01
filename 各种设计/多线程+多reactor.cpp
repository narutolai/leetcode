#include <stdio.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/types.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <netdb.h>
#include <errno.h>
#include <pthread.h>
#define MAX_EVENT 1000
#define READ_BUF_LEN 256

/**
 * 设置 file describe 为非阻塞模式
 * @param fd 文件描述
 * @return 返回0成功，返回-1失败
 */
static int make_socket_non_blocking (int fd) {
    int flags, s;
    // 获取当前flag
    flags = fcntl(fd, F_GETFL, 0);
    if (-1 == flags) {
        perror("Get fd status");
        return -1;
    }

    flags |= O_NONBLOCK;

    // 设置flag
    s = fcntl(fd, F_SETFL, flags);
    if (-1 == s) {
        perror("Set fd status");
        return -1;
    }
    return 0;
}


#define MAX_THREAD_NUM 128
int ithreadnum = 0;

typedef struct ListNode
{
    int connfd;
    struct ListNode* next;
    ListNode(int con, ListNode*pNode = NULL):connfd(con),next(pNode){}
} ListNode;
struct ThreadData 
{
    int id;
    pthread_t tid;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    struct ListNode* head;
    struct ListNode* tail;
};
extern int RegConfd(int connfd, int epfd);
struct ThreadData threaddata[MAX_THREAD_NUM]={0};

void * threadFunc(void* arg)
{
    int i = *(int*)arg;
//    printf("num i ==:%d \n",i);
    int epfd = epoll_create1(0);
    if (1 == epfd) {
        perror("Create epoll instance");
        return 0;
    }

    struct epoll_event  event[MAX_EVENT];
    //客户端描述符通过这个队列 然后线程取拿到描述符进行监听
    // 总是就是需要一个数据传递的地方
    //这个就是多reactor模式
    while(1){
        //TODO 这里要使用简单的生成者消费者模型
        pthread_mutex_lock(&(threaddata[i].mutex));//卧槽这不是挂起啊 这个是锁呀
        while(threaddata[i].head == NULL)
        {
 //           printf("head is null waiting.....:%d \n",i);
            pthread_cond_wait(&threaddata[i].cond, &threaddata[i].mutex);
        }
        struct ListNode *head = threaddata[i].head;
        while(head != NULL)
        {
            printf("thread:%d, proc connfd:%d\n", i, head->connfd);
            //注册连接，描述符
            RegConfd(head->connfd , epfd);
            //注册完后立马销毁
            // 头节点指向下一个
            threaddata[i].head = threaddata[i].head->next;
            delete head;
            head = threaddata[i].head;
        }
        pthread_mutex_unlock(&threaddata[i].mutex);
        //epoll_wait
        int wait_count;
        // 等待事件
        wait_count = epoll_wait(epfd, event, MAX_EVENT, -1);
        for (int j = 0 ; j < wait_count; j++) 
        {
            int connfd  = event[j].data.fd;
            int iret = 0;
            while(1)//ET模式 我们把数据读取完
            {
                char buf[100];
                iret = recv(connfd, buf, 100, 0);
                if(iret > 0)
                {
                    printf("thread: %d deal with connfd:%d,recv  data:%s\n",i, connfd, buf );
                }
                else
                {
                    break;
                }
            }
        }
    }
}

int RegConfd(int accp_fd, int epfd)
{
    // listen的 file describe 事件触发， accpet事件
    int   __result = make_socket_non_blocking(accp_fd);
    if (-1 == __result) {
        return 0;
    }
    struct epoll_event ev;
    ev.data.fd = accp_fd;
    ev.events = EPOLLIN | EPOLLET;
    // 为新accept的 file describe 设置epoll事件
    //     因为这个交给特定的子线程 所以这里就不需要监听了
    __result = epoll_ctl(epfd, EPOLL_CTL_ADD, accp_fd, &ev);

    if (-1 == __result) {
        perror("epoll_ctl");
        return 0;
    }

    if (-1 == __result) {
        perror("epoll_ctl");
        return 0;
    }
    return 0;
}
void createthread(int num)
{
    //in= 0;
    //ithreadnum ;
    for ( ithreadnum = 0; ithreadnum < num;  ithreadnum++ )
    {
        threaddata[ithreadnum].id = ithreadnum;
        threaddata[ithreadnum].cond= PTHREAD_COND_INITIALIZER;
        threaddata[ithreadnum].mutex = PTHREAD_MUTEX_INITIALIZER;
        pthread_create(&(threaddata[ithreadnum].tid), NULL, threadFunc, (void*)&threaddata[ithreadnum].id);
    }
}
void addconn2thread(int connfd)
{
    struct ThreadData &thdata  = threaddata[connfd % ithreadnum];
    struct ListNode *pNode =  new ListNode(connfd, NULL);
    pNode->next = NULL;
    if(thdata.head == NULL)
    {
        thdata.head= pNode;
        thdata.tail = thdata.head;
    }
    else
    {
        thdata.tail->next = pNode;
        thdata.tail  = thdata.tail->next;
    }
    pthread_cond_broadcast(&thdata.cond);
}
int main(int argc ,char *argv[])
{
    if(argc < 2)
    {
        printf("useage:%s, count",argv[0]);
        return -1;
    }
    int num = atoi(argv[1]);
  
    createthread(num);   
    // epoll 实例 file describe
    int epfd = 0;
    int listenfd = 0;
    int result = 0;
    struct epoll_event ev, event[MAX_EVENT];
    // 绑定的地址
    const char * const local_addr = "127.0.0.1";
    struct sockaddr_in server_addr = { 0 };

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == listenfd) {
        perror("Open listen socket");
        return -1;
    }
    /* Enable address reuse */
    int on = 1;
    // 打开 socket 端口复用, 防止测试的时候出现 Address already in use
    result = setsockopt( listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on) );
    if (-1 == result) {
        perror ("Set socket");
        return 0;
    }

    server_addr.sin_family = AF_INET;
    inet_aton (local_addr, &(server_addr.sin_addr));
    server_addr.sin_port = htons(8080);
    result = bind(listenfd, (const struct sockaddr *)&server_addr, sizeof (server_addr));
    if (-1 == result) {
        perror("Bind port");
        return 0;
    }
    result = make_socket_non_blocking(listenfd);
    if (-1 == result) {
        return 0;
    }

    result = listen(listenfd, 500);
    if (-1 == result) {
        perror("Start listen");
        return 0;
    }

    // 创建epoll实例
    epfd = epoll_create1(0);
    if (1 == epfd) {
        perror("Create epoll instance");
        return 0;
    }

    ev.data.fd = listenfd;
    ev.events = EPOLLIN | EPOLLET /* 边缘触发选项。 */;
    // 设置epoll的事件
    result = epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev);

    if(-1 == result) {
        perror("Set epoll_ctl");
        return 0;
    }
    
    
    for ( ; ; ) {
        int wait_count;
        // 等待事件
        wait_count = epoll_wait(epfd, event, MAX_EVENT, -1);

        for (int i = 0 ; i < wait_count; i++) {
            uint32_t events = event[i].events;
            // IP地址缓存
            char host_buf[NI_MAXHOST];
            // PORT缓存
            char port_buf[NI_MAXSERV];

            int __result;
            // 判断epoll是否发生错误
            if ( events & EPOLLERR || events & EPOLLHUP || (! events & EPOLLIN)) {
                printf("Epoll has error\n");
                close (event[i].data.fd);
                continue;
            } else if (listenfd == event[i].data.fd) {

               for ( ; ; ) { // 由于采用了边缘触发模式，这里需要使用循环
                    struct sockaddr in_addr = { 0 };
                    socklen_t in_addr_len = sizeof (in_addr);
                    int accp_fd = accept(listenfd, &in_addr, &in_addr_len);
                    if (-1 == accp_fd) {
                        perror("Accept");
                        break;
                    }
                    __result = getnameinfo(&in_addr, sizeof (in_addr),
                                           host_buf, sizeof (host_buf) / sizeof (host_buf[0]),
                                           port_buf, sizeof (port_buf) / sizeof (port_buf[0]),
                                           NI_NUMERICHOST | NI_NUMERICSERV);

                    if (! __result) {
                        printf("New connection:%d host = %s, port = %s\n",accp_fd ,host_buf, port_buf);
                    }

                    addconn2thread(accp_fd);
                }
                continue;
            } else {
            }
        }
    }
    for(int i =0; i< ithreadnum ;++i)
    {
        pthread_join(threaddata[i].tid, NULL);
    }
    close (epfd);
    return 0;
}

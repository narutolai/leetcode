
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <pthread.h>
#include <assert.h>
#include <sys/wait.h>
#include <sys/stat.h>

//处理信号的管道 以实现统一事件源
#define MAX_EVENT_NUMBER 1024
static int sig_pipefd[2];

int setnoblocking(int fd)
{
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}

void addfd(int epollfd, int fd)
{
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
    setnoblocking(fd);
}

void removefd(int epollfd, int fd)
{
    epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, 0);
    close(fd);
}

/*信号处理函数*/
static void sig_handler(int sig)
{
    //保留原来的errno 在函数最后恢复，以保证函数的可重入性
    int save_errno = errno;
    int msg = sig;
    send(sig_pipefd[1], (char *)&msg, 1, 0); //将信号值写入管道以通知主循坏
    errno = save_errno;
}
//设置信号处理函数
static void addsig(int sig, void(handler)(int), bool restart = true)
{
    struct sigaction sa;
    memset(&sa, '\0', sizeof(sa));
    sa.sa_handler = sig_handler;
    if (restart)
    {
        sa.sa_flags |= SA_RESTART;
    }
    sigfillset(&sa.sa_mask);
    assert(sigaction(sig, &sa, NULL) != -1);
}

int main(int argc, char *argv[])
{
    if (argc <= 2)
    {
        printf("usage :%s ip_address port_number\n", basename(argv[0]));
        return 1;
    }
    const char *ip = argv[1];
    int port = atoi(argv[2]);

    int ret = 0;
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;

    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    int listenfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(listenfd >= 0);

    ret = bind(listenfd, (struct sockaddr *)&address, sizeof(address));
    if (ret == -1)
    {
        printf("errno is %d\n", errno);
        return 1;
    }
    ret = listen(listenfd, 5);
    assert(ret != -1);

    epoll_event events[MAX_EVENT_NUMBER];
    int epollfd = epoll_create(5);

    assert(epollfd != -1);
    addfd(epollfd, listenfd);

    //使用socketpairt 创建管道 注册pipefd[0]上的可读事件

    ret = socketpair(PF_UNIX, SOCK_STREAM, 0, sig_pipefd);
    assert(ret != -1);

    setnoblocking(sig_pipefd[1]);
    addfd(epollfd, sig_pipefd[0]);

    //设置一些信号处理函数

    addsig(SIGHUP);
    addsig(SIGCHLD);
    addsig(SIGTERM);
    addsig(SIGINT);

    bool stop_server = false;

    while (!stop_server)
    {
        int number = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1);
        if ((number < 0) && (errno != EINTR))
        {
            printf("epoll failure \n") break;
        }

        for (int i = 0; i < number; i++)
        {
            int sockfd = events[i].data.fd;
            //处理新的连接
            if (sockfd == listenfd)
            {
                struct sockaddr_in client_address;
                socklen_t client_addlength = sizeof(client_address);
                int connfd = accept(listenfd, (struct sockaddr *)&client_address, &client_addlength);
                addfd(epollfd, connfd);
            }
            else if ((sockfd == sig_pipefd[0]) && (events[i].events & EPOLLIN))
            {
                int sig;
                char signal[1024];
                ret =recv(sig_pipefd[0],signal,sizeof(signal),0);
                if(ret ==-1)
                {
                    continue;
                }
                else if(ret== 0)
                {
                    continue;
                }
                else
                {
                    for(int i =0 ;i <ret; ++i)
                    {
                        switch (signal[i])
                        {
                        case SIGCHLD:
                        case SIGHUP:
                        {
                            continue;
                        }
                        case SIGTERM:
                        case SIGINT:
                        {
                            stop_server =true;
                        }
                        }
                    }
                }
            }
            else
            {

            }
        }
    }
    printf("close fd\n");
    close(listenfd);
    close(sig_pipefd[1]);
    close(sig_pipefd[0]);
    return 0;
}
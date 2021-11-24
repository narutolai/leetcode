#ifndef PROCESSPOLL_H
#define PROCESSPOLL_H

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

//描述一个子进程的类
class process
{
public:
	process() : m_pid(-1) {}

public:
	pid_t m_pid;	 //子进程id
	int m_pipefd[2]; //子进程和父进程通信的管道
};

//进程池类 模板参数是处理逻辑任务的类
template <typename T>
class processpool
{
private:
	//将构造函数设置为私有，因此我们只能通后面的create静态函数来创建processpool实例
	processpool(int listenfd, int process_number = 8);

public:
	//单例模式 最多创建一个实例 只需要一个池
	static processpool<T> *create(int listenfd, int process_number = 8)
	{
		if (!m_instance)
		{
			m_instance = new processpool<T>(listenfd, process_number);
		}
		return m_instance;
	}
	~processpool()
	{
		delete[] m_sub_process;
	}
	//启动进程池
	void run();

private:
	void setup_sig_pipe();
	void run_parent();
	void run_child();

private:
	//进程池允许的最大子进程数量
	static const int MAX_PROCESS_NUMBER = 16;
	//每一个子进程最多可以处理的客户端数量
	static const int USER_PER_PROCESS = 65536;
	//epoll 最多可以处理的事件数
	static const int MAX_EVENT_NUMBER = 10000;
	//进程池中的进程数量
	int m_process_number;
	//子进程在池中的序号 从0开始
	int m_idx;
	//每一个进程都有一个epollfd
	int m_epollfd;
	//监听socket
	int m_listenfd;
	//子进程通过m_stop来决定是否停止运行
	int m_stop;
	//保存所有子进程的描述信息
	process *m_sub_process;
	//进程池静态实例
	static processpool<T> *m_instance;
};

template <typename T>
processpool<T> *processpool<T>::m_instance = NULL;

//处理信号的管道 以实现统一事件源
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

//进程池构造函数
template <typename T>
processpool<T>::processpool(int listenfd, int process_number) : m_listenfd(listenfd), m_process_number(process_number), m_idx(-1), m_stop(false)
{
	assert((process_number > 0) && (process_number <= MAX_PROCESS_NUMBER));

	m_sub_process = new process[process_number];
	assert(m_sub_process);
	//创建process_number个子进程,并且建立他们和父进程之间的管道
	for (int i = 0; i < process_number; i++)
	{
		//使用socketpair()建立的pipefd
		int ret = socketpair(PF_UNIX, SOCK_STREAM, 0, m_sub_process[i].m_pipefd);
		assert(ret == 0);

		//创建子进程 子进程的m_pid都是0 父进程是-1
		m_sub_process[i].m_pid = fork();
		assert(m_sub_process[i].m_pid >= 0); //=0子进程 >0父进程

		if (m_sub_process[i].m_pid > 0) //父进程的m_pid就是子进程pid
		{
			//父进程关闭写管道
			close(m_sub_process[i].m_pipefd[1]);
			continue;
		}
		else
		{
			//子进程关闭读管道 子进程运行到这里就可以break了 但是父进程还是要继续运行的
			close(m_sub_process[i].m_pipefd[0]);
			m_idx = i;
			break;
		}
	}
}

//统一事件源
template <typename T>
void processpool<T>::setup_sig_pipe()
{
	//创建epoll事件监听表和信号管道
	m_epollfd = epoll_create(5);
	assert(m_epollfd != -1);

	int ret = socketpair(PF_UNIX, SOCK_STREAM, 0, sig_pipefd);
	assert(ret != -1);

	setnoblocking(sig_pipefd[1]);
	//设置信号处理函数
	addsig(SIGCHLD, sig_handler);
	addsig(SIGTERM, sig_handler);
	addsig(SIGINT, sig_handler);
	addsig(SIGPIPE, SIG_IGN);
}

//父进程中m_idx值为-1  子进程中m_idx>0 我们据此判断接下来要运行的是父进程代码还是子进程代码
template <typename T>
void processpool<T>::run()
{
	if (m_idx != -1)
	{
		run_child();
		return;
	}
	run_parent();
}

template <typename T>
void processpool<T>::run_parent()
{
	setup_sig_pipe();

	//父进程监听listenfd
	addfd(m_epollfd, m_listenfd);
	epoll_event events[MAX_EVENT_NUMBER];

	int sub_process_counter = 0;
	int new_conn = 1;
	int number = 0;
	int ret = -1;

	while (!m_stop)
	{
		number = epoll_wait(m_epollfd, events, MAX_EVENT_NUMBER, -1);
		if ((number < 0) && (errno != EINTR))
		{
			printf("epoll failure\n");
			break;
		}
		for (int i = 0; i < number; i++)
		{
			int sockfd = events[i].data.fd;
			//如果有客户端连接 连接
			if (sockfd == m_listenfd)
			{
				//如果有新的连接到来 就将其分配一个子进程处理
				int i = sub_process_counter;
				do
				{
					if (m_sub_process[i].m_pid != -1)
					{
						break;
					}

					i = (i + 1) % m_process_number;

				} while (i != sub_process_counter);

				if (m_sub_process[i].m_pid == -1)
				{
					m_stop = true;
					break;
				}
				//下一个待选的子进程id。
				sub_process_counter = (i + 1) % m_process_number;

				//要哪个子进程处理 就向哪个子进程的管道写1
				send(m_sub_process[i].m_pipefd[0], (char *)&new_conn, sizeof(new_conn), 0);

				printf("send request to child %d\n", i);
			} //处理父进程接受到信号
			else if ((sockfd == sig_pipefd[0]) && (events[i].events & EPOLLIN))
			{
				int sig;
				char signals[1024];
				ret = recv(sig_pipefd[0], signals, sizeof(signals), 0);
				if (ret <= 0)
				{
					continue;
				}
				else
				{
					for (int i = 0; i < ret; i++)
					{
						switch (signals[i])
						{
						case SIGCHLD: //子进程终止时向父进程发送该信号
						{
							pid_t pid;
							int stat;
							while ((pid = waitpid(-1, &stat, WNOHANG)) > 0)
							{
								for (int i = 0; i < m_process_number; i++)
								{
									//找到对应的子进程 关掉该进程的pipefd的0端因为 写端已经关闭了
									if (m_sub_process[i].m_pid == pid)
									{
										printf("child %d join\n", i);
										close(m_sub_process[i].m_pipefd[0]);
										m_sub_process[i].m_pid = -1;
									}
								}
							}
							//如果所有的子进程都推出了 父进程也退出
							m_stop = true;
							for (int i = 0; i < m_process_number; i++)
							{
								if (m_sub_process[i].m_pid != -1)
								{
									m_stop = false;
								}
							}
							break;
						}
						case SIGTERM:
						case SIGINT:
						{
							//如果父进程收到终止信号，那么就杀死所有的子进程，并且等他们全部结束
							printf("kill all the child now \n");
							for (int i = 0; i < m_process_number; i++)
							{
								int pid = m_sub_process[i].m_pid;
								if (pid != -1)
								{
									kill(pid, SIGTERM);
								}
							}
							break;
						}
						default:
						{
							break;
						}
						}
					}
				}
			}
			else
			{
				continue;
			}
		}
	}
	//listenfd不是子进程创建的 所以不该由它关掉
	//	close(listenfd);
	close(m_epollfd);
}

template <typename T>
void processpool<T>::run_child()
{
	setup_sig_pipe();
	//每一个子进程都通过在进程池中的序号值m_idx找到与父进程通信的管道
	int pipefd = m_sub_process[m_idx].m_pipefd[1];
	//子进程需要监听管道文件描述符pipefd 因为父进程将通过它来通知子进程accept新连接
	addfd(m_epollfd, pipefd);

	epoll_event events[MAX_EVENT_NUMBER];

	T *users = new T[USER_PER_PROCESS];

	assert(users);

	int number = 0;
	int ret = -1;

	while (!m_stop)
	{
		number = epoll_wait(m_epollfd, events, MAX_EVENT_NUMBER, -1);
		if ((number < 0) && (errno != EINTR))
		{
			printf("epoll failure\n");
			break;
		}
		for (int i = 0; i < number; i++)
		{
			int sockfd = events[i].data.fd;
			//父进程把connfd 告知子进程
			if (sockfd == pipefd && (events[i].events & EPOLLIN)) //如果pipe[0]上有可读事件 可能有信号了
			{
				int client = 0;
				ret = recv(sockfd, (char *)&client, sizeof(client), 0);

				if (((ret < 0) && errno != EAGAIN) || ret == 0)
				{
					continue;
				}
				else
				{
					//告诉你有连接  然后你自己去连
					struct sockaddr_in cliaddr;
					socklen_t cliaddrlen = sizeof(cliaddr);
					int connfd = accept(m_listenfd, (struct sockaddr *)&cliaddr, &cliaddrlen);
					printf("a socket descriptor for connfd :%d\n", connfd);
					if (connfd < 0)
					{
						printf("errno is %d\n", errno);
						continue;
					}
					addfd(m_epollfd, connfd);
					//模板类T必须实现init方法以初始化一个客户连接我们直接使用connfd来索引逻辑处理对象 以提高程序的效率
					users[connfd].init(m_epollfd, connfd, cliaddr);
				}
			} //处理接受到信号 全局外部信号
			else if ((sockfd == sig_pipefd[0]) && (events[i].events & EPOLLIN))
			{
				int sig;
				char signals[1024];
				ret = recv(sig_pipefd[0], signals, sizeof(signals), 0);
				if (ret <= 0)
				{
					continue;
				}
				else
				{
					for (int i = 0; i < ret; i++)
					{
						switch (signals[i])
						{
						case SIGCHLD:
						{
							pid_t pid;
							int stat;
							while ((pid = waitpid(-1, &stat, WNOHANG)) > 0)
							{
								continue;
							}
							break;
						}
						case SIGTERM:
						case SIGINT:
						{
							m_stop = true;
							break;
						}
						default:
						{
							break;
						}
						}
					}
				}
			} //客户端和子进程的通信 调用逻辑对象的process 方法处理之 其实就是connfd上有数据
			else if (events[i].events & EPOLLIN)
			{
				users[sockfd].process();
			}
			else
			{
				continue;
			}
		}
	}
	delete[] users;
	users = NULL;

	//listenfd不是子进程创建的 所以不该由它关掉
	//close(listenfd);
	close(pipefd);
	close(m_epollfd);
}

#endif

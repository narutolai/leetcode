#ifndef LST_TIMER
#define LST_TIMER

#include <time.h>
#define BUFFER_SIZE 64
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
class util_timer;

struct client_data
{
	struct sockaddr_in address;
	int sockfd;
	char buf[BUFFER_SIZE];
	util_timer *timer;
};

//定时器类
class util_timer
{
public:
	util_timer() : prev(NULL), next(NULL) {}

public:
	time_t expire;
	void (*cb_func)(client_data *);

	client_data *user_data;

	util_timer *prev;
	util_timer *next;
};

//定时器链表  升序双向链表

class sort_time_lst
{
public:
	sort_time_lst() : head(NULL), tail(NULL) {}
	~sort_time_lst()
	{
		util_timer *tmp = head;
		while (tmp)
		{
			head = tmp->next;
			delete tmp;
			tmp = head;
		}
	}
	void add_timer(util_timer *timer)
	{
		if (!timer)
		{
			return;
		}
		if (!head)
		{
			head = tail = timer;
			return;
		}
		//目标定时器的超时时间小于当前链表中的所有的定时器的超时时间，插入到第一个节点
		if (timer->expire < head->expire)
		{
			timer->next = head;
			head->prev = timer;
			head = timer;
			return;
		}
		add_timer(timer, head);
	}
	//一个定时器的时间延长了所以要调整该定时器 我们只考虑时间延长情况
	void adjust_timer(util_timer *timer)
	{
		if (!timer)
			return;
		util_timer *tmp = timer->next;
		if (!tmp || (timer->expire < tmp->expire))
			return;
		if (timer == head)
		{
			head = head->next;
			head->prev = NULL;
			timer->next = NULL;
			add_timer(timer, head);
		}
		else
		{
			timer->prev->next = timer->next;
			timer->next->prev = timer->prev;
			add_timer(timer, timer->next);
		}
	}
	void del_timer(util_timer *timer)
	{
		if (!timer)
			return;
		if ((timer == head) && (timer == tail))
		{
			delete timer;
			head = NULL;
			tail = NULL;
		}
		if (timer == head)
		{
			head = head->next;
			head->prev = NULL;
			delete timer;
			return;
		}

		if (timer == tail)
		{
			tail = tail->prev;
			tail->next = NULL;
			delete timer;
			return;
		}

		timer->prev->next = timer->next;
		timer->next->prev = timer->prev;
		delete timer;
	}
	void tick()
	{
		if (!head)
			return;
		printf("timer tick\n");

		time_t cur = time(NULL);
		util_timer *tmp = head;
		//从头开始遍历所有的定时器 一直到遇到一个尚未到期的定时器 这就是定时器的核心逻辑
		while (tmp)
		{
			if (cur < tmp->expire)
				break;
			//执行定时任务
			tmp->cb_func(tmp->user_data);

			head = tmp->next;
			if (head)
				head->prev = NULL;
			delete tmp;
			tmp = head;
		}
	}

private:
	void add_timer(util_timer *timer, util_timer *lst_head)
	{
		util_timer *prev = lst_head;
		util_timer *tmp = prev->next;

		while (tmp)
		{
			if (timer->expire < tmp->expire)
			{
				prev->next = timer;
				timer->next = tmp;
				tmp->prev = timer;
				timer->prev = prev;
				break;
			}
			prev = tmp;
			tmp = tmp->next;
		}
		if (!tmp)
		{
			prev->next = timer;
			timer->prev = prev;
			timer->next = NULL;
			tail = timer;
		}
	}

private:
	util_timer *head;
	util_timer *tail;
};

int main()
{
}
#endif

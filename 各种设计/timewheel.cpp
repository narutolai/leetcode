#ifndef TIME_WHEEL_TIMER
#define TIME_WHEEL_TIMER
#include <time.h>
#include <netinet/in.h>
#include <stdio.h>

#define BUFFER_SIZE 64
class tw_timer;

struct client_data
{
	sockaddr_in address;
	int sockfd;
	char buf[BUFFER_SIZE];
	tw_timer *timer;
};

class tw_timer
{
public:
	tw_timer(int rot, int ts) : next(NULL), prev(NULL), rotation(rot), time_slot(ts) {}

public:
	int rotation;
	int time_slot;
	void (*cb_func)(client_data *);
	client_data *user_data;
	tw_timer *next;
	tw_timer *prev;
};
class time_wheel
{
public:
	time_wheel() : cur_slot(0)
	{
		for (int i = 0; i < N; ++i)
		{
			slots[i] = NULL;
		}
	}
	~time_wheel()
	{
		//遍历每一个槽 并销毁其中的定时器
		for (int i = 0; i < N; ++i)
		{
			tw_timer *tmp = slots[i];
			while (tmp)
			{
				slots[i] = tmp->next;
				delete tmp;
				tmp = slots[i];
			}
		}
	}
	//根据timeout 创建一个定时器 并且把他插入到合适的槽中
	tw_timer *add_timer(int timeout)
	{
		if (timeout < 0)
		{
			return NULL;
		}
		int ticks = 0;
		if (timeout < SI)
		{
			ticks = 1;
		}
		else
		{
			ticks = timeout / SI;
		}
		//总之 我们就要根据超时时间 来确定一个定时器的rotation和ts
		int rotation = ticks / N;
		int ts = (cur_slot + (ticks % N)) % N;
		tw_timer *timer = new tw_timer(rotation, ts);

		//如果
		if (!slots[ts])
		{
			slots[ts] = timer;
		}
		else
		{
			timer->next = slots[ts];
			slots[ts]->prev = timer;
			slots[ts] = timer;
		}
		return timer;
	}
	void del_timer(tw_timer *timer)
	{
		if (!timer)
			return;
		int ts = timer->time_slot;
		//如果是首节点
		if (timer == slots[ts])
		{
			slots[ts] = slots[ts]->next;
			if (slots[ts])
			{
				slots[ts]->prev = NULL;
			}
			delete timer;
		}
		else
		{
			timer->prev->next = timer->next;
			if (timer->next)
			{
				timer->next->prev = timer->prev;
			}
			delete timer;
		}
	}
	void tick()
	{
		tw_timer *tmp = slots[cur_slot];
		while (tmp)
		{
			if (tmp->rotation > 0)
			{
				tmp->rotation--;
				tmp = tmp->next;
			}
			else
			{
				tmp->cb_func(tmp->user_data);
				//如果是首节点
				if (tmp == slots[cur_slot])
				{
					slots[cur_slot] = tmp->next;
					delete tmp;
					if (slots[cur_slot])
					{
						slots[cur_slot]->prev = NULL;
					}
					tmp = slots[cur_slot];
				}
				else
				{
					tmp->prev->next = tmp->next;
					if (tmp->next)
					{
						tmp->next->prev = tmp->prev;
					}
					tw_timer *tmp2 = tmp->next;
					delete tmp;
					tmp = tmp2;
				}
			}
		}
		cur_slot = ++cur_slot % N;
	}
private:
	static const int N = 60;
	static const int SI = 1;
	tw_timer *slots[N];
	int cur_slot;
};
int main()
{
}
#endif

class MyQueue
{
public:
	stack<int> st1;
	stack<int> st2;
	/** Initialize your data structure here. */
	MyQueue()
	{
	}

	/** Push element x to the back of queue. */
	void push(int x)
	{
		st1.push(x);
	}

	/** Removes the element from in front of queue and returns that element. */
	int pop()
	{
		if (!empty())
		{
			int a=peek();
			st2.pop();
			return a;
		}
        return 0;
	}

	/** Get the front element. */
	int peek()
	{
		if (!empty())
		{
			if (!st2.empty())
				return st2.top();

			while (!st1.empty())
			{
				st2.push(st1.top());
				st1.pop();
			}
			return st2.top();
		}
        return 0;
	}

	/** Returns whether the queue is empty. */
	bool empty()
	{
		return st1.empty() && st2.empty();
	}
};
//±éÀú´ÎÊý +1
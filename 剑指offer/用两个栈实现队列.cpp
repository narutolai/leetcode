

class CQueue {
public:

    stack<int> a;
    stack<int> b; 
    CQueue() {

    }
    //总结就是：入队操作就是进栈a,出队列操作就是 把b的栈顶元素弹出，如果b空 就从a那里取
    //队尾插入操作 
    void appendTail(int value) {
        a.push(value);
    }
    //队头删除操作
    int deleteHead() {
        if(a.empty()&&b.empty()) return -1; //b和a都空时
        else if(b.empty()&&!a.empty()) //b空a不空时
        {   
            while(!a.empty())  //把a所有的元素都弹出到b中，
            {
                b.push(a.top());
                a.pop();
            }
        }
        int temp=b.top();  //取b的栈顶元素 返回
        b.pop();
        return temp;
    }
};


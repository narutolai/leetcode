//一个简单消息队列的实现

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>

struct msgqueue
{
    void *memory; //可以存放消息的起始地址
    int bufsize;//申请的字节数
    int msgnum; //当前消息条数
    int getoff; // 拿消息的起始偏移
    int putoff;   //放消息的起始偏移

};

typedef struct msgqueue msgqueue;

#define BUFSIZE 1024

msgqueue* getqueue()
{
    msgqueue *msg = (msgqueue*)malloc(sizeof(msgqueue) + BUFSIZE);
    msg->memory = msg + sizeof(msgqueue);
    msg->bufsize =  BUFSIZE;
    msg->msgnum = 0;
    msg->putoff = 0;
    msg->getoff = 0;
    return msg;
}


void _put_msg(msgqueue* msgqu , char *msg, int msglen)
{
    void *putadd = msgqu->memory + msgqu->putoff;
    strncpy(putadd, (char*)&msglen, 4);
    msgqu->putoff += 4;
    strncpy(putadd + 4, msg, msglen);
    msgqu->putoff += msglen ;
    msgqu->msgnum++;
}


void put_msg( msgqueue* msgqu , char *msg, int msglen)
{
    //剩余空间不够放一条消息怎么办
    int leftspace  = msgqu->getoff + msgqu->bufsize - msgqu->putoff;
    if(leftspace >= msglen + 4)//消息长度
    {
        if(msgqu->bufsize - msgqu->putoff >= msglen + 4)
        {
            _put_msg(msgqu, msg, msglen);
        }
        else
        {
            int inmsglen = msgqu->putoff -  msgqu->getoff;
            strncpy( msgqu->memory , msgqu->memory + msgqu->getoff, inmsglen);
            msgqu->getoff = 0;
            msgqu->putoff = inmsglen;
            _put_msg(msgqu, msg, msglen);
        }
    }
    else
    {
        //没有空间放消息了
        //wait..... 在寻找一块更大的区域?? 比如 2*BUFSIZE 的大小
        printf("no left space\n");
    }
}

void get_msg(msgqueue* msgqu , char *buf, int buflen)
{
    if(msgqu->getoff == msgqu->putoff)
    {
        printf("no message get....");
    }
    else
    {
        void *getadd = msgqu->memory + msgqu->getoff;
        char msglen[4];
        strncpy(msglen, getadd, 4);
        msgqu->getoff += 4;
        int len = buflen < *(int*)msglen ? buflen : *(int*)msglen ;  //注意这里要取最小值   
        strncpy(buf, getadd + 4 ,len);
        msgqu->getoff += len;
        msgqu->msgnum--;
    }
}

int main()
{
    msgqueue *msgq = getqueue();

    char *msg="hello world";
    put_msg(msgq, msg, strlen(msg));

    char *msg1="narutolai";
    put_msg(msgq, msg1, strlen(msg1));

    char *msg2="laishengyu";
    put_msg(msgq, msg2, strlen(msg2));
    
    char buf[20];
    get_msg(msgq, buf, 20);
    printf("msg1: %s\n",buf);
    
    memset(buf, 0, 20);
    
    get_msg(msgq, buf,20);
    printf("msg2: %s\n", buf);
    
    memset(buf, 0 , 20);
    
    get_msg(msgq, buf, 20);
    printf("msg3: %s\n", buf);


    return 0;
}




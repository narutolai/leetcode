/*client_tcp.c*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>



int socknum= 0;
int sockarr[2000];
int main(int argc ,char**argv){
    if(argc < 2)
    {
        printf("useage:%s, count",argv[0]);
        return -1;
    }
    //创建套接字
    while(socknum < atoi(argv[1]))
    {
        int sock = socket(AF_INET, SOCK_STREAM, 0);

        //服务器的ip为本地，端口号1234
        struct sockaddr_in serv_addr;
        memset(&serv_addr, 0, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        serv_addr.sin_port = htons(8080);

        //向服务器发送连接请求
        int ret = connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
        if(ret)
        {
            printf("connect error\n");
            break;
        }
        sockarr[socknum++] = sock;
    }
    //发送并接收数据
    for(int i = 0;  i < socknum;++i)
    {
        send(sockarr[i], "hello", 6, 0);
    }
    //断开连接
    sleep(100);

    return 0;
}


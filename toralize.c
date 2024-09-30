/* toralize.c */
//项目入口文件

#include "toralize.h"

int main(int argc, char *argv[]){
    char *host;
    int port, s;
    struct  sockaddr_in sock;
    //校验控制台参数，如果参数少于3个格式化打印输出提示字符串
    if(argc < 3){
        fprintf(stderr,"Usage: %s <host> <port> \n", argv[0]);
        return -1;
    }

    host = argv[1]; //包括程序名在内，第二个参数是ip
    port = atoi(argv[2]); //第三个参数为端口。并把字符转化为数字

    s = socket(AF_INET,SOCK_STREAM,0); // tcp类型
    if(s<0){
        perror("socket");
        return -1;
    }

    sock.sin_family = AF_INET;
    sock.sin_port = htons(PROXYPORT);
    sock.sin_addr.s_addr = inet_addr(PROXY);
    //连接：extern int connect(int __fd, const sockaddr *__addr, socklen_t __len)
    if(connect(s,(struct sockaddr *)&sock,sizeof(sock))){
        perror("Connect");//连接失败
        return -1;
    };

    printf("conected to proxy \n");
    close(s);
    return  0;
}

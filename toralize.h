//
// Created by lee on 24-10-1.
//

#include <stdio.h>
#include <stdlib.h>  // atoi:字符转数字函数
#include <string.h>
#include <unistd.h> // close

// 控制台 man 3 address命令可以查询到这三个包
#include <sys/socket.h> //socket包， man 2 socket 查询包路径，2表示系统调用
#include <arpa/inet.h> //htons()
#include <netinet/in.h> // inet_addr

/**
socket();//初始化socket函数
connect();//连接socket函数
close();//关闭socket函数
htons(); //处理二进制端口号
inet_addr();//处理大ip直，使其在二进制流中正确表示 man 3 inet_addr 查询函数所在包。3表示库
*/
//定义本地Ip和端口号
#define PROXY       "127.0.0.1"
#define PROXYPORT   9050
typedef unsigned char       int8; //1字节
typedef unsigned short int  int16; //2字节
typedef unsigned int        int32; //4字节
/** socket连接请求协议
+----+----+----+----+----+----+----+----+----+----+....+----+
| VN | CD | DSTPORT |      DSTIP        | USERID       |NULL|
+----+----+----+----+----+----+----+----+----+----+....+----+
  1    1      2              4           variable         1
*/

struct proxy_request{
    int8 vn; //protocol version number :4 --> socket4
    int8 cd; //the result code with one of the following values:90: request granted 91: request rejected or failed 92: request rejected becasue SOCKS server cannot connect to identd on the client 93: request rejected because the client program and identd
    int16 dstport; //连接端口
    int32 dstip; // 连接ip地址
    unsigned char userid[8]; // 可变用户id
};
typedef struct proxy_request Req; // 创建Req结构

/** socket连接响应协议
+----+----+----+----+----+----+----+----+
| VN | CD | DSTPORT |      DSTIP        |
+----+----+----+----+----+----+----+----+
  1    1      2              4
*/
struct proxy_response{
    int8 vn;
    int8 cd;
    //响应不需要返回端口和ip
    int16 _;
    int32 __;
};
typedef struct proxy_response Res; //创建响应结构体
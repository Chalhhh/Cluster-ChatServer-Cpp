#ifndef CHATSERVER_H
#define CHATSERVER_H
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
using namespace muduo;
using namespace muduo::net;

// 聊天服务器的主类
class ChatServer
{
public:
    // 初始化对象 
    ChatServer(EventLoop* loop,
            const InetAddress& listenAddr,
            const string& nameArg);
    
    // 启动服务
    void start();

private:
    TcpServer _server;   // muoduo 库组合对象
    EventLoop* _loop;     // 循环事件对象

    // 上报连接相关信息的 回调函数
    void onConnection(const TcpConnectionPtr&);

    // 上报读写时间相关信息的 回调函数
    void onMessage(const TcpConnectionPtr&,
                            Buffer*,
                            Timestamp);
};


#endif
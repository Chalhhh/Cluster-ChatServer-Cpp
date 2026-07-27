#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <functional>
#include <string>
#include <iostream>
using namespace std;
using namespace muduo;
using namespace muduo::net;
using namespace placeholders;

// epoll + 线程池
// 能把网路 I/O 的代码和业务代码区分开
// 用户的连接和断开 用户的可读写时间

// 基于muduo网络库开发服务器程序
// 1. 组合TcpServer对象
// 2. 创建EventLoop事件循环对象的指针
// 3. 明确TcpServer构造函数需要什么参数，输出
// 4. 在当前服务器类的构造函数当中，注册处理连接的回调函数和处理读写事件的回调函数
// 5. 设置合适的服务端线程数量，muduo库会自己分配I/O线程和worker线程

class ChatServer
{
public:
    ChatServer(EventLoop* loop,             // 事件循环 
            const InetAddress& listenAddr,  // IP + Port
            const string& nameArg)          // 服务器的名字
            : _server(loop, listenAddr, nameArg)
            , _loop(loop)
    {
        // 给服务器注册用户连接的创建和断开回调  | 事件发生的时间和位置不明确  
        // 底层的epoll_wait 、accept已经封装
        // typedef std::function<void (const TcpConnectionPtr&)> ConnectionCallback;  
        // 指针保存了Socket套接字，后续所有read() / write() / close()
        _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, _1)); // 直接调用该函数

        // 给服务器注册用户读写事件回调
        _server.setMessageCallback(std::bind(&ChatServer::onMessage, this, _1, _2, _3));

        // 设置服务器端的线程数量  | 一个I/O线程 3个worker线程
        _server.setThreadNum(4); 
    }


    void start()
    {
        _server.start();
    }



private:
    // 专门处理用户的连接创建和断开  epoll listenfd  accept 
    // 方法会响应 成员方法为了访问成员方法
    void onConnection(const TcpConnectionPtr& conn)
    {
        if (conn->connected())
        {
            // 返回 InetAddress  封装 ip + port
            cout << conn->peerAddress().toIpPort() << "->" << conn->localAddress().toIpPort() << " state:online" << endl;
        }
        else
        {
            cout << conn->peerAddress().toIpPort() << "->" << conn->localAddress().toIpPort() << " state:offline" << endl;
            conn->shutdown();  // close(fd) 连接断开
            // _loop->quit();  退出epoll
        }
        
    }

    // 专门处理用户的读写事件
    void onMessage(const TcpConnectionPtr& conn,    // 连接
                            Buffer* buffer,         // 缓冲区
                            Timestamp time)         // 接收到数据的时间信息
    {
        string buf = buffer->retrieveAllAsString();
        cout << "recv data:" << buf << "time:" << time.toString() << endl;
        conn->send(buf);
    }

    TcpServer _server;  // #1 没有默认构造
    EventLoop *_loop;   // #2 epoll

};

int main()
{
    EventLoop loop;   // epoll
    InetAddress addr("127.0.0.1", 6000);
    ChatServer server(&loop, addr, "ChatServer");
    server.start();  // listenfd epoll_ctl -> epoll
    loop.loop();     // epoll_wait以阻塞方式等待新用户连接，已连接用户的读写事件等

    return 0;
}
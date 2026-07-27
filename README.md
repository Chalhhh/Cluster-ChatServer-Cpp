# Cluster-ChatServer-Cpp
基于 C++ Muduo 引擎与 Nginx 负载均衡构建的高并发集群聊天系统。结合 Redis 消息队列解耦跨服通信，支持海量连接与平滑横向扩展。

- 编译方式
mkdir build
cd build
cmake ..
make

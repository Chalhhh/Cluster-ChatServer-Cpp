#ifndef USERMODEL_H
#define USERMODEL_H
#include "user.hpp"

// 1. 业务层 收到客户端的json，解析出name和password
// 2. 创建User对象
// 3. 调用共UserModel惊醒持久化
// 封装具体的SQl操作
// User表的数据操作类
class UserModel
{
public:
    // User表的增加方法
    bool insert(User& user);

    // 根据用户号码查询用户信息
    User query(int id);

    // 更新用户的状态信息
    bool updateState(User user);

    // 重置用户的状态信息
    void resetState();

};
#endif
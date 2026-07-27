#ifndef GROUP_H
#define GROUP_H
#include "groupuser.hpp"
#include <vector>
using namespace std;


// User表的ORM类
class Group
{
public:
    Group(int id = -1, string name = "", string desc = "")
    {
        this->id = id;
        this->name = name;
        this->desc = desc;
    }

    // 群的基本属性
    void setId(int id) {this->id = id;}             // 设置群组id
    void setName(string name) {this->name = name;}  // 设置群名
    void setDesc(string desc) {this->desc = desc;}  // 设置群描述

    int getId() {return this->id;}         
    string getName() {return this->name;}  
    string getDesc() {return this->desc;}  
    vector<GroupUser>& getUsers() {return this->users;}

private:
    int id;                    // 群组id信息
    string name;               // 群组名
    string desc;               // 群组描述
    vector<GroupUser> users;   // 群组成员信息

};




#endif
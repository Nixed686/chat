#include "usermodel.hpp"
#include "db.h"
#include <iostream>
using namespace std;

//User表的增加方式
bool UserModel::insert(User &user)
{
    //1，组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "insert into User(name, password, state) values('%s', '%s', '%s')",    //此处与视频不同本数据库表名首字母大写，视频中为小写。
        user.getName().c_str(), user.getPwd().c_str(), user.getState().c_str());
    
    MySQL mysql;
    if(mysql.connect())
    {
        if(mysql.update(sql))
        {
            //获取插入成功的用户数据生成的主键id
            user.setId(mysql_insert_id(mysql.getconnection()));
            return true;
        }
    }
    return false;
}

//根据用户号码查询用户信息
User UserModel::query(int id)
{
    //1，组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "select *from User where id = %d",id);         //此处与视频不同本数据库表名首字母大写，视频中为小写
    
    MySQL mysql;
    if(mysql.connect())
    {
        MYSQL_RES *res = mysql.query(sql);
        if (res != nullptr)
        {
            MYSQL_ROW row = mysql_fetch_row(res);
            if (row != nullptr)
            {
                User user;
                user.setId(atoi(row[0]));
                user.setName(row[1]);
                user.setPwd(row[2]);
                user.setState(row[3]);
                mysql_free_result(res);
                return user;
            }
        }
    }
    return User();
}

//更新用户状态信息
bool UserModel::updateState(User user)
{
    char sql[1024] = {0};
    sprintf(sql, "update User set state = '%s' where id = %d", user.getState().c_str(), user.getId());         //此处与视频不同本数据库表名首字母大写，视频中为小写
    
    MySQL mysql;
    if(mysql.connect())
    {
        if (mysql.update(sql))
        {
            return true;
        }
    }
    return false;
}

//重置所有用户的状态信息
void UserModel::resetState()
{
    //组装sql语句
    char sql[1024] = "update User set state = 'offline' where state = 'online'";

    MySQL mysql;
    if(mysql.connect())
    {
        mysql.update(sql);
    }
}
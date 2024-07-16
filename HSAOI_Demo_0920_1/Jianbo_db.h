#ifndef JIANBO_DB_H
#define JIANBO_DB_H

#include "log_singleton.h"
#include <QDateTime>
#include <QHash>
#include <QSharedPointer>
#include <QSqlDatabase>
#include <QSqlRecord>

#define HOSTNAME "127.0.0.1"
#define DATABASENAME "DaTuo"
#define USERNAME "haoshi"
#define PASSWORD "123456"

struct GlassDataBaseInfo{
    QDateTime time;
    int id;
    double length;
    double width;
    QString q;
    int num;
    QString GlassType;
    int qipao;
    int jieshi;
    int zhanxi;
    int huashang;
    int liewen;
    int zangwu;
    int bengbian;
    int bengjiao;
    int daojiao;
    int bianbuliewen;
};

class Jianbo_db {

public:
    QSqlDatabase db;

public:
    explicit Jianbo_db();
    bool openDataBase();    // 打开数据库
    bool insertOneData(const GlassDataBaseInfo& data);   //插入数据库
    bool updateData();      //更新数据库
    bool deleteData();      //删除数据库
    bool queryData();       //查询数据库
    bool closeDataBase();   //关闭数据库
};

#endif // JIANBO_DB_H

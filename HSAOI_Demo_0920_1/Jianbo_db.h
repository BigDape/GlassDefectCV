#ifndef JIANBO_DB_H
#define JIANBO_DB_H

#include "log_singleton.h"
#include <QDateTime>
#include <QHash>
#include <QSharedPointer>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <unordered_map>
#include "FlawDefine.h"

#define HOSTNAME "127.0.0.1"
#define DATABASENAME "DaTuo"
#define USERNAME "haoshi"
#define PASSWORD "123456"



//单例模式
class Jianbo_db {
private:
    Jianbo_db();
    Jianbo_db(Jianbo_db&) = delete;
    Jianbo_db& operator=(const Jianbo_db&) = delete;
public:
    ~Jianbo_db(){}
    static Jianbo_db* GetInstance();

    bool openDataBase();    // 打开数据库
    bool insertOneData(const GlassDataBaseInfo& data);   //插入数据库
    bool insertOneData(const GlassSizeInfo& data);       //插入数据库
    bool insertOneData(const GlassDefect& data);         //插入数据库

    bool updateData(const GlassDataBaseInfo& data);      //更新数据库
    bool updateData(const GlassSizeInfo& data);      //更新数据库
    bool updateData(const GlassDefect& data);      //更新数据库

    bool deleteGlassTableData(int id);      //删除数据库
    bool deleteGlassDefectData(int id);      //删除数据库
    bool deleteGlassSizeinfoData(int id);      //删除数据库

    bool queryTableData(std::vector<GlassDataBaseInfo>& datas, QString querySql);       //查询数据库
    bool queryTableData(std::vector<GlassSizeInfo>& datas, QString querySql);       //查询数据库
    bool queryTableData(std::vector<GlassDefect>& datas, QString querySql);       //查询数据库
    bool closeDataBase();   //关闭数据库

public:
    int getNextID(QString tableName); //获取tableName表的下一个id
    int getNewGlassTable();
public:
    QSqlDatabase db;
};

#endif // JIANBO_DB_H

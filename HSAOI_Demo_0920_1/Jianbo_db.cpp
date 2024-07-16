#include "Jianbo_db.h"

#include <QDateTime>
#include <QDebug>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#pragma execution_character_set("utf-8")

Jianbo_db::Jianbo_db()
{
    qDebug()<<QSqlDatabase::drivers(); //查看QT支持的驱动
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(HOSTNAME);                   // server name
    db.setDatabaseName(DATABASENAME);           // database name
    db.setUserName(USERNAME);                   // user name for login
    db.setPassword(PASSWORD);                   // passward
    QString createGlassTable="Create table glass_table \
                             (id  bigint Not Null, \
                              info bigint Not Null, \
                              benbian bigint Not Null, \
                              benjiao bigint Not Null, \
                              jiejingdian bigint Not Null, \
                               zsg
                              ";
    db.exec();
}


bool Jianbo_db::openDataBase()
{
    if (db.open()) {
        log_singleton::Write_Log("已连接到数据库！", General);

    } else {
        log_singleton::Write_Log(db.lastError().text(), Error);
    }

    return true;
}

bool Jianbo_db::insertOneData(const GlassDataBaseInfo& data)
{
//    QSqlQuery db_insert(db);

//    if (!connect_flag) {
//        log_singleton::Write_Log("数据库未连接！", Error);
//    } else {

//        db_insert.prepare(
//            "USE [Jianbo]"
//            "INSERT INTO [dbo].[Glass_Info]"
//            "([检测时间],[玻璃ID],[长度],[宽度],[质量],[缺陷数量],[玻璃规格]"
//            ",[气泡],[结石],[沾锡],[划伤],[裂纹],[脏污],[崩边],[崩角],[倒角],[边部裂纹])"
//            "VALUES(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");

//    }

//    if (db_insert.exec()) {
//        log_singleton::Write_Log("数据已保存至数据库！", Log_Level::General);
//    } else {
//        log_singleton::Write_Log(db_insert.lastError().text(), Log_Level::Error);
//    }

//    QSqlQuery query;
//    QString sql = QString("INSERT INTO petfeeder (interval, temperature, weight) "
//                              "VALUES (%1, %2, %3)").arg(interval).arg(temperature).arg(weight);
//        bool ret = query.exec(sql);
//        if (!ret) {
//            qDebug() << "Failed to insert data: " << query.lastError().text();
//        }
}

bool Jianbo_db::updateData()
{

}

bool Jianbo_db::deleteData()
{

}

bool Jianbo_db::queryData()
{

}

bool Jianbo_db::closeDataBase()
{
    if(db.isOpen()) {
        db.close();
    }
}

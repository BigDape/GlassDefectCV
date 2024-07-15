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
    db = QSqlDatabase::addDatabase("QODBC");

    // server name
    db.setHostName(hostname);

    // database name
    db.setDatabaseName(databasename);

    // user name for login
    db.setUserName(username);

    // passward
    db.setPassword(password);

    // initialize database connect status
    connect_flag = false;
}

// connect to database
bool Jianbo_db::start_connect()
{
    // connect status
    connect_flag = db.open();

    if (connect_flag) {
        log_singleton::Write_Log("已连接到数据库！", General);

    } else {
        log_singleton::Write_Log(db.lastError().text(), Error);
    }

    return connect_flag;
}

// insert data to database
void Jianbo_db::start_insert(QDateTime time, int id, double length, double width, QString q, int num, QString GlassType,
    int qipao, int jieshi, int zhanxi, int huashang, int liewen, int zangwu, int bengbian, int bengjiao, int daojiao, int bianbuliewen)
{

    QSqlQuery db_insert(db);

    if (!connect_flag) {
        log_singleton::Write_Log("数据库未连接！", Error);
    } else {

        db_insert.prepare(
            "USE [Jianbo]"
            "INSERT INTO [dbo].[Glass_Info]"
            "([检测时间],[玻璃ID],[长度],[宽度],[质量],[缺陷数量],[玻璃规格]"
            ",[气泡],[结石],[沾锡],[划伤],[裂纹],[脏污],[崩边],[崩角],[倒角],[边部裂纹])"
            "VALUES(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");

        db_insert.addBindValue(time);
        db_insert.addBindValue(id);
        db_insert.addBindValue(length);
        db_insert.addBindValue(width);
        db_insert.addBindValue(q);
        db_insert.addBindValue(num);
        db_insert.addBindValue(GlassType);
        db_insert.addBindValue(qipao);
        db_insert.addBindValue(jieshi);
        db_insert.addBindValue(zhanxi);
        db_insert.addBindValue(huashang);
        db_insert.addBindValue(liewen);
        db_insert.addBindValue(zangwu);
        db_insert.addBindValue(bengbian);
        db_insert.addBindValue(bengjiao);
        db_insert.addBindValue(daojiao);
        db_insert.addBindValue(bianbuliewen);
    }

    if (db_insert.exec()) {
        log_singleton::Write_Log("数据已保存至数据库！", Log_Level::General);
    } else {
        log_singleton::Write_Log(db_insert.lastError().text(), Log_Level::Error);
    }
}

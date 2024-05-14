#ifndef JIANBO_DB_H
#define JIANBO_DB_H

#include "log_singleton.h"
#include <QDateTime>
#include <QHash>
#include <QSharedPointer>
#include <QSqlDatabase>
#include <QSqlRecord>

using namespace std;

class Jianbo_db {

public:
    QSqlDatabase db;

    QString hostname = "127.0.0.1";

    QString databasename = "Jianbo";

    QString username = "haoshi";

    QString password = "123456";

public:
    bool connect_flag; // database connect status

public:
    Jianbo_db();

    bool start_connect(); // connect to database

    void start_insert(QDateTime time, int id, double length, double width, QString q, int num, QString GlassType,
        int qipao, int jieshi, int zhanxi, int huashang, int liewen, int zangwu, int bengbian, int bengjiao,
        int daojiao, int bianbuliewen); // insert data to database
};

#endif // JIANBO_DB_H

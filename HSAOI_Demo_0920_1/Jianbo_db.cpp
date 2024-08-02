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
    qDebug()<<QSqlDatabase::drivers();          //查看QT支持的驱动
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(HOSTNAME);                   // server name
    db.setDatabaseName(DATABASENAME);           // database name
    db.setUserName(USERNAME);                   // user name for login
    db.setPassword(PASSWORD);                   // passward
}


Jianbo_db* Jianbo_db::GetInstance()
{
    static Jianbo_db instance;
    return &instance;
}

bool Jianbo_db::openDataBase()
{
    if (db.open()) {
        qDebug()<<"已连接到数据库！";
        //创建数据统计
        QString createGlassTable = "CREATE TABLE IF NOT EXISTS glass_table"
                                 "(id INTEGER PRIMARY KEY AUTOINCREMENT, \
                                  time TEXT, OKorNG TEXT, sizeOKorNG TEXT, \
                                  length REAL, width REAL, duijiaoxian1 REAL, \
                                  duijiaoxian2 REAL, defectNumber INTEGER, defectOKorNG TEXT, \
                                  huashanNumber INTEGER, qipaoNumber INTEGER, jieshiNumber INTEGER, \
                                  benbianNumber INTEGER, zanwuNumber INTEGER, liewenNumber INTEGER, qitaNumber INTEGER)";

        //创建glass_defect
        QString createGlassDefectTable="CREATE TABLE IF NOT EXISTS glass_defect"
                                        "(id INTEGER PRIMARY KEY AUTOINCREMENT, \
                                         defectid INTEGER, time TEXT, defectype INTEGER, \
                                         defectlevel INTEGER, X REAL, Y REAL, \
                                         length REAL,width REAL, area REAL, glassid INTEGER, ImagePath TEXT)";

        //创建glass_sizeinfo，孔洞、丝印、门夹
        QString createGlassSizeInfo = "CREATE TABLE IF NOT EXISTS glass_sizeinfo"
                "(id INTEGER PRIMARY KEY AUTOINCREMENT, \
                 sizeno INTEGER, time TEXT, sizeType TEXT, sizeLevel TEXT, \
                 lengthX REAL, widthY REAL, marginsX REAL, marginsY REAL, glassid INTEGER, ImagePath TEXT)";

        QSqlQuery query(db);
        if(!query.exec(createGlassTable)) {
            qDebug() << "Create table glass_table is fail.";
        } else {
            qDebug() << "成功创建glass_table或者已经存在.";
        }
        QSqlQuery query1(db);
        if(!query1.exec(createGlassDefectTable)) {
            qDebug() << "Create table glass_defect is fail.";
        } else{
            qDebug() << "成功创建glass_defect或者已经存在.";
        }
        QSqlQuery query2(db);
        if(!query2.exec(createGlassSizeInfo)) {
            qDebug() << "Create table glass_sizeinfo is fail.";
        } else {
            qDebug() << "成功创建glass_sizeinfo或者已经存在.";
        }
    } else {
        //log_singleton::Write_Log(db.lastError().text(), Error);
        qDebug()<<db.lastError().text();
        return false;
    }
    return true;
}

bool Jianbo_db::insertOneData(const GlassDataBaseInfo& data)
{
    QSqlQuery query(db);
    QString sql = QString("INSERT INTO glass_table"
                          "(id, time, OKorNG, sizeOKorNG, length, width, duijiaoxian1, duijiaoxian2, defectNumber, defectOKorNG, "
                          "huashanNumber, qipaoNumber, jieshiNumber, benbianNumber, zanwuNumber, liewenNumber, qitaNumber)"
                          "VALUES (%1, '%2', '%3', '%4', %5, %6, %7, %8, %9, '%10', %11, %12, %13, %14, %15, %16, %17)")
                          .arg(data.id)
                          .arg(data.time)
                          .arg(data.OKorNG)
                          .arg(data.sizeOKorNG)
                          .arg(data.length)
                          .arg(data.width)
                          .arg(data.duijiaoxian1)
                          .arg(data.duijiaoxian2)
                          .arg(data.defectNumber)
                          .arg(data.defectOKorNG)
                          .arg(data.huashanNumber)
                          .arg(data.qipaoNumber)
                          .arg(data.jieshiNumber)
                          .arg(data.benbianNumber)
                          .arg(data.zanwuNumber)
                          .arg(data.liewenNumber)
                          .arg(data.qitaNumber);
    qDebug()<<sql;
    if (!query.exec(sql)) {
        qDebug() << "Failed to insert data: " << query.lastError().text();
        return false;
    }
    return true;
}

bool Jianbo_db::insertOneData(const GlassSizeInfo& data)
{
    QSqlQuery query(db);
    QString sqlGlassSizeInfo = QString("INSERT INTO glass_sizeinfo (id, sizeno, time, sizeType, sizeLevel, lengthX, widthY, marginsX, marginsY, glassid, ImagePath)"
                                  "VALUES (%1, %2, '%3', '%4', '%5', %6, %7, %8, %9, %10, '%11')")
                                  .arg(data.id)
                                  .arg(data.sizeno)
                                  .arg(data.time)
                                  .arg(data.sizeType)
                                  .arg(data.sizeLevel)
                                  .arg(data.lengthX)
                                  .arg(data.widthY)
                                  .arg(data.marginsX)
                                  .arg(data.marginsY)
                                  .arg(data.glassid)
                                  .arg(data.imagePath);
    qDebug()<<sqlGlassSizeInfo;
    if (!query.exec(sqlGlassSizeInfo)) {
        qDebug() << "Failed to insert data: " << query.lastError().text();
        return false;
    }
    return true;
}

bool Jianbo_db::insertOneData(const GlassDefect& data)
{
    QSqlQuery query(db);
    QString sqlGlassDefect=QString("INSERT INTO glass_defect(id, defectid, time, defectype, defectlevel, X, Y, length, width,area, glassid, ImagePath)"
                                "VALUES (%1, %2, '%3', '%4', '%5', %6, %7, %8, %9, %10, %11, '%12')")
                .arg(data.id)
                .arg(data.defectId)
                .arg(data.time)
                .arg(data.defectType)
                .arg(data.defectLevel)
                .arg(data.x)
                .arg(data.y)
                .arg(data.length)
                .arg(data.width)
                .arg(data.area)
                .arg(data.glassid)
                .arg(data.imagePath);
   qDebug()<<sqlGlassDefect;
   if (!query.exec(sqlGlassDefect)) {
       qDebug() << "Failed to insert data: " << query.lastError().text();
       return false;
   }
   return true;
}

bool Jianbo_db::updateData(const GlassDataBaseInfo& data)
{
    QSqlQuery query(db);
    QString sql = QString("UPDATE glass_table SET time='%1', OKorNG='%2', sizeOKorNG='%3', length=%4, width=%5, duijiaoxian1=%6, duijiaoxian2=%7, defectNumber=%8, defectOKorNG='%9',"
                          "huashanNumber=%10, qipaoNumber=%11, jieshiNumber=%12, benbianNumber=%13, zanwuNumber=%14, liewenNumber=%15, qitaNumber=%16 WHERE id=%17")
            .arg(data.time)
            .arg(data.OKorNG)
            .arg(data.sizeOKorNG)
            .arg(data.length)
            .arg(data.width)
            .arg(data.duijiaoxian1)
            .arg(data.duijiaoxian2)
            .arg(data.defectNumber)
            .arg(data.defectOKorNG)
            .arg(data.huashanNumber)
            .arg(data.qipaoNumber)
            .arg(data.jieshiNumber)
            .arg(data.benbianNumber)
            .arg(data.zanwuNumber)
            .arg(data.liewenNumber)
            .arg(data.qitaNumber)
            .arg(data.id);
    qDebug()<< sql;
    if (!query.exec(sql)) {
        qDebug() << "Failed to update data: " << query.lastError().text();
        return false;
    }
    return true;
}

bool Jianbo_db::updateData(const GlassSizeInfo& data)
{
    QSqlQuery query(db);
    QString sql = QString("UPDATE glass_sizeinfo SET sizeno=%1, time='%2', sizeType='%3', sizeLevel='%4', lengthX=%5, widthY=%6, "
                          "marginsX=%7, marginsY=%8, glassid=%9, ImagePath='%10'  WHERE id=%11")
            .arg(data.sizeno)
            .arg(data.time)
            .arg(data.sizeType)
            .arg(data.sizeLevel)
            .arg(data.lengthX)
            .arg(data.widthY)
            .arg(data.marginsX)
            .arg(data.marginsY)
            .arg(data.glassid)
            .arg(data.imagePath)
            .arg(data.id);
    qDebug()<< sql;
    if (!query.exec(sql)) {
        qDebug() << "Failed to update data: " << query.lastError().text();
        return false;
    }
    return true;
}

bool Jianbo_db::updateData(const GlassDefect& data)
{
    QSqlQuery query(db);
    QString sql = QString("UPDATE glass_defect SET defectid=%1, time='%2', defectype='%3', defectlevel='%4', X=%5, Y=%6, length=%7, width=%8, area=%9,"
                          "glassid=%10, ImagePath='%11' WHERE id=%12")
            .arg(data.defectId)
            .arg(data.time)
            .arg(data.defectType)
            .arg(data.defectLevel)
            .arg(data.x)
            .arg(data.y)
            .arg(data.length)
            .arg(data.width)
            .arg(data.area)
            .arg(data.glassid)
            .arg(data.imagePath)
            .arg(data.id);
    qDebug()<< sql;
    if (!query.exec(sql)) {
        qDebug() << "Failed to update data: " << query.lastError().text();
        return false;
    }
    return true;
}

bool Jianbo_db::deleteGlassTableData(int id)
{
    QSqlQuery query(db);
    QString sql = QString("DELETE FROM glass_table WHERE id=%1").arg(id);
    qDebug()<< sql;
    if (!query.exec(sql)) {
       qDebug() << "Failed to delete data: " << query.lastError().text();
       return false;
    }
    return true;
}

bool Jianbo_db::deleteGlassDefectData(int id)
{
    QSqlQuery query(db);
    QString sql = QString("DELETE FROM glass_defect WHERE id=%1").arg(id);
    qDebug()<< sql;
    if (!query.exec(sql)) {
       qDebug() << "Failed to delete data: " << query.lastError().text();
       return false;
    }
    return true;
}

bool Jianbo_db::deleteGlassSizeinfoData(int id)
{
    QSqlQuery query(db);
    QString sql = QString("DELETE FROM glass_sizeinfo WHERE id=%1").arg(id);
    qDebug()<< sql;
    if (!query.exec(sql)) {
       qDebug() << "Failed to delete data: " << query.lastError().text();
       return false;
    }
    return true;
}

bool Jianbo_db::queryTableData(std::vector<GlassDataBaseInfo>& datas,QString querySql)
{
    QSqlQuery query(db);
    qDebug()<<querySql;
    if(!query.exec(querySql)) {
        qDebug() << "Failed to query data: " << query.lastError().text();
        return false;
    }
    while (query.next()) {
        GlassDataBaseInfo data;
        data.id= query.value(0).toInt();
        qDebug()<<"data.id="<<data.id;
        data.time = query.value(1).toString();
        qDebug()<<"data.time="<<data.time;
        data.OKorNG = query.value(2).toString();
        qDebug()<<"data.OKorNG="<<data.OKorNG;
        data.sizeOKorNG = query.value(3).toString();
        qDebug()<<"data.sizeOKorNG="<<data.sizeOKorNG;
        data.length = query.value(4).toDouble();
        qDebug()<<"data.length="<<data.length;
        data.width = query.value(5).toDouble();
        qDebug()<<"data.width="<<data.width;
        data.duijiaoxian1 = query.value(6).toDouble();
        qDebug()<<"data.duijiaoxian1="<<data.duijiaoxian1;
        data.duijiaoxian2 = query.value(7).toDouble();
        qDebug()<<"data.duijiaoxian2="<<data.duijiaoxian2;
        data.defectNumber = query.value(8).toInt();
        qDebug()<<"data.defectNumber="<<data.defectNumber;
        data.defectOKorNG = query.value(9).toString();
        qDebug()<<"data.defectOKorNG="<<data.defectOKorNG;
        data.huashanNumber = query.value(10).toInt();
        qDebug()<<"data.huashanNumber="<<data.huashanNumber;
        data.qipaoNumber = query.value(11).toInt();
        qDebug()<<"data.qipaoNumber="<<data.qipaoNumber;
        data.jieshiNumber = query.value(12).toInt();
        qDebug()<<"data.jieshiNumber="<<data.jieshiNumber;
        data.benbianNumber = query.value(13).toInt();
        qDebug()<<"data.benbianNumber="<<data.benbianNumber;
        data.zanwuNumber = query.value(14).toInt();
        qDebug()<<"data.zanwuNumber="<<data.zanwuNumber;
        data.liewenNumber = query.value(15).toInt();
        qDebug()<<"data.liewenNumber="<<data.liewenNumber;
        data.qitaNumber = query.value(16).toInt();
        qDebug()<<"data.qitaNumber="<<data.qitaNumber;
        datas.push_back(data);
    }
    return true;
}

bool Jianbo_db::queryTableData(std::vector<GlassSizeInfo>& datas, QString querySql)
{
    QSqlQuery query(db);
    qDebug()<<querySql;
    if(!query.exec(querySql)) {
        qDebug() << "Failed to query data: " << query.lastError().text();
        return false;
    }
    while (query.next()) {
        GlassSizeInfo data;
        data.id= query.value(0).toInt();
        qDebug()<<"data.id="<<data.id;
        data.sizeno = query.value(1).toInt();
        qDebug()<<"data.sizeno ="<<data.sizeno;
        data.time = query.value(2).toString();
        qDebug()<<"data.time ="<<data.time;
        data.sizeType = query.value(3).toString();
        qDebug()<<"data.sizeType ="<<data.sizeType;
        data.sizeLevel = query.value(4).toString();
        qDebug()<<"data.sizeLevel ="<<data.sizeLevel;
        data.lengthX = query.value(5).toDouble();
        qDebug()<<"data.lengthX ="<<data.lengthX;
        data.widthY = query.value(6).toDouble();
        qDebug()<<"data.widthY ="<<data.widthY;
        data.marginsX = query.value(7).toDouble();
        qDebug()<<"data.marginsX ="<<data.marginsX;
        data.marginsY = query.value(8).toDouble();
        qDebug()<<"data.marginsY ="<<data.marginsY;
        data.glassid = query.value(9).toInt();
        qDebug()<<"data.glassid ="<<data.glassid;
        data.imagePath = query.value(10).toString();
        qDebug()<<"data.imagePath ="<<data.imagePath;
        datas.push_back(data);
    }
    return true;
}

bool Jianbo_db::queryTableData(std::vector<GlassDefect>& datas, QString querySql)
{
    QSqlQuery query(db);
    qDebug()<<querySql;
    if(!query.exec(querySql)) {
        qDebug() << "Failed to query data: " << query.lastError().text();
        return false;
    }
    while (query.next()) {
        GlassDefect data;
        data.id= query.value(0).toInt();
        qDebug()<<"data.id="<<data.id;
        data.defectId = query.value(1).toInt();
        qDebug()<<"data.defectId ="<<data.defectId;
        data.time = query.value(2).toString();
        qDebug()<<"data.time = "<<data.time;
        data.defectType = query.value(3).toString();
        qDebug()<<"data.defectType ="<<data.defectType;
        data.defectLevel = query.value(4).toString();
        qDebug()<<"data.defectLevel ="<<data.defectLevel;
        data.x = query.value(5).toDouble();
        qDebug()<<"data.x ="<<data.x;
        data.y = query.value(6).toDouble();
        qDebug()<<"data.y ="<<data.y;
        data.length = query.value(7).toDouble();
        qDebug()<<"data.length ="<<data.length;
        data.width = query.value(8).toDouble();
        qDebug()<<"data.width ="<<data.width;
        data.area = query.value(9).toDouble();
        qDebug()<<"data.area ="<<data.area;
        data.glassid = query.value(10).toInt();
        qDebug()<<"data.glassid ="<<data.glassid;
        data.imagePath = query.value(11).toString();
        qDebug()<<"data.imagePath ="<<data.imagePath;
        datas.push_back(data);
    }
    return true;
}


bool Jianbo_db::closeDataBase()
{
    if(db.isOpen()) {
        db.close();
    }
    return true;
}

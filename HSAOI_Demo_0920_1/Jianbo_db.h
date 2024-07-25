﻿#ifndef JIANBO_DB_H
#define JIANBO_DB_H

#include "log_singleton.h"
#include <QDateTime>
#include <QHash>
#include <QSharedPointer>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <unordered_map>

#define HOSTNAME "127.0.0.1"
#define DATABASENAME "DaTuo"
#define USERNAME "haoshi"
#define PASSWORD "123456"

//单个缺陷信息
struct GlassDefect{
    size_t id;              // 主键id,在所有缺陷中的顺序
    int defectId;           // 缺陷id，在一块玻璃中缺陷的顺序
    QString time;           // 缺陷检测时间
    QString defectType;     // 缺陷类型
    QString defectLevel;    // 缺陷等级，OK NG
    double x;               // 缺陷在玻璃上的X坐标
    double y;               // 缺陷在玻璃上的Y坐标
    double length;          // 缺陷的长度
    double width;           // 缺陷的宽度
    double area;            // 缺陷面积大小
    size_t glassid;         // 外键id,玻璃的id
    QString imagePath;      // 缺陷图片的路径
};

// 孔洞、门夹、丝印信息
struct GlassSizeInfo{
    size_t id;              // 主键id,玻璃尺寸信息的顺序id
    int sizeno;             // 孔、门夹、丝印排列顺序
    QString time;           // 时间
    QString sizeType;       // 类型
    QString sizeLevel;      // 等级
    double lengthX;         // 长X(mm)
    double widthY;          // 宽Y(mm)
    double marginsX;        // 边距X(mm)
    double marginsY;        // 边距Y(mm)
    size_t glassid;         // 外键id,玻璃的id
    QString imagePath;      // 缺陷图片的路径
};

//数据统计信息
struct GlassDataBaseInfo{
    size_t id;                                              // 玻璃的id，唯一的主键
    QString time;                                           // 时间
    QString OKorNG;         // 整体情况OK或者NG
    QString sizeOKorNG;     // 尺寸OK或者NG
    double length;          // 玻璃的长度
    double width;           // 玻璃的宽度
    double duijiaoxian1;    // 玻璃的对角线1
    double duijiaoxian2;    // 玻璃的对角线2
    int defectNumber;       // 玻璃的缺陷数量
    QString defectOKorNG;   // 缺陷OK或者NG
    int huashanNumber;      // 划伤数量
    int qipaoNumber;        // 气泡数量
    int jieshiNumber;       // 结石数量
    int benbianNumber;      // 崩边数量
    int zanwuNumber;        // 脏污数量
    int liewenNumber;       // 裂纹数量
    int qitaNumber;         // 其它数量
};

struct GlassInfoDefect{
    size_t glassid;              // 主键id,玻璃的顺序id
    GlassDataBaseInfo baseinfo;
    std::unordered_map<size_t, GlassSizeInfo> kongdong;         // 孔洞
    std::unordered_map<size_t,GlassSizeInfo> menjia;          // 门夹
    std::unordered_map<size_t,GlassSizeInfo> siyin;             // 丝印
    std::unordered_map<size_t, GlassDefect> huashang;           // 划伤
    std::unordered_map<size_t, GlassDefect> qipao;              // 气泡
    std::unordered_map<size_t, GlassDefect> jieshi;             // 结石
    std::unordered_map<size_t, GlassDefect> benbian;            // 崩边
    std::unordered_map<size_t, GlassDefect> zanwu;              // 脏污
    std::unordered_map<size_t, GlassDefect> liewen;             // 裂纹
    std::unordered_map<size_t, GlassDefect> qita;               // 其他
};


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

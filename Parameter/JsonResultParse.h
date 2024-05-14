#ifndef JSONRESULTPARSE_H
#define JSONRESULTPARSE_H
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QDebug>

class JsonResultParse
{
public:
    JsonResultParse();
    ~JsonResultParse();

    struct DetectResult
    {
      QString Time;
      QString GlassID;
      QString GlassLength;
      QString GlassWidth;
      QString GlassAngle; //偏移的角度

      QStringList DefectID;
      QStringList DefectType;
      QStringList DefectLeve;
      QStringList Width;
      QStringList Lenth;
      QStringList X;
      QStringList Y;
      QStringList Area;
      QStringList ImageNGPath;

      QStringList HolesID;
      QStringList Type;
      QStringList HolesLeve;
      QStringList DistanceHorizontal;
      QStringList DistanceVertical;
      QStringList HolesWidth;
      QStringList HolesHeight;
      QStringList ImageHolesPath;
      QString ImageHolesLinePath;
    };
    DetectResult ResultData;
    QJsonObject jsonObj;
    QJsonDocument jsonDoc;
    QJsonObject jsonObjSK;
    QJsonDocument jsonDocSK;
    // 创建二级键值对数据
    QJsonObject nestedData;
    void ini_JsonResult();
    QString InterParasToQJson(DetectResult ResultData, int DefectStartCount, int DefectCount, int ProcessStep ,int HolesCount, bool isDefect);
};

#endif // JSONRESULTPARSE_H

#include "JsonParse2Map.h"
#include "log_singleton.h"
#include<QDebug>
#pragma execution_character_set("utf-8")

JsonParse2Map::JsonParse2Map(QString FileName)
{
    m_filepath = FileName;
    ReadParamsFromFile();
}

void createNestedJsonObject2(QJsonObject& parentObject,
    const QList<QString>& keys,
    int depth,
    QString finalValue,
    int ValueType)
{
    if (depth >= keys.size()) {
        return;
    }

    QString currentKey = keys.at(depth);// 获取当前深度对应的键
    if (depth == keys.size() - 1) {// 如果已经是最终深度，根据值类型插入最终值
        if (ValueType == J4_FLOAT64_MAP)
            parentObject[currentKey] = finalValue.toDouble();
        else

            parentObject[currentKey] = finalValue;
    } else {
        // 如果不是最终深度
        // 检查父对象中是否已经包含当前键
        if (!parentObject.contains(currentKey)) {
              // 如果不包含，创建一个空的 JSON 对象并插入到父对象中
            parentObject[currentKey] = QJsonObject();
        }
        // 获取当前键对应的 JSON 对象
        QJsonObject currentObject = parentObject[currentKey].toObject();
        // 递归调用函数，创建更深层次的 JSON 结构
        createNestedJsonObject2(currentObject, keys, depth + 1, finalValue,ValueType);
        // 将创建好的 JSON 对象插入到父对象中
        parentObject[currentKey] = currentObject;
    }
}

int JsonParse2Map::SaveParamsToFile()
{
    QJsonObject jsonObject;
    QMap<QString, _VALUE_ELEMENT4JSON_MAP>::iterator i;

    for (i = MAPTABLE.begin(); i != MAPTABLE.end(); i++) {
        QString Origin = i.key();
        QList<QString> Parents;
        while (Origin.contains(".")) {
            int DotIndex = Origin.indexOf(".");
            if (DotIndex != -1) {
                QString extractedString = Origin.left(DotIndex);
                Parents.append(extractedString);
                Origin = Origin.mid(DotIndex + 1);
            }
        }
        Parents.append(Origin);
        createNestedJsonObject2(jsonObject, Parents, 0, i.value().value,
            i.value().valType);
    }

    QJsonDocument jsonDoc(jsonObject);

    QString jsonString = jsonDoc.toJson(QJsonDocument::Indented);
    qDebug() <<"jsonString"<< jsonString;
    QFile jsonFile(m_filepath);
    if (jsonFile.open(QIODevice::WriteOnly)) {
        QTextStream stream(&jsonFile);
        stream.setCodec("UTF-8");
        stream << jsonString;
        jsonFile.close();
        log_singleton::Write_Log("写入Json文件成功", Log_Level::General);
         qDebug() << "写入Json文件成功";
    } else {
        log_singleton::Write_Log("写入Json文件错误", Log_Level::Error);
        qDebug() << "写入Json文件错误";
    }
    return 0;
}

int JsonParse2Map::ReadParamsFromFile()
{
    int ret = ParseJsonFile(m_filepath);
    return ret;
}

int JsonParse2Map::ChangeParams(QString FileName)
{
    m_filepath = FileName;
    MAPTABLE.clear();
    if (ReadParamsFromFile())
        return 0;
    else
        return -1;
}

bool JsonParse2Map::setParameter(QString name, double& value)
{
    bool b_ret = MAPTABLE.contains(name);
    if (b_ret) {
        QMap<QString, _VALUE_ELEMENT4JSON_MAP>::iterator _iter;
        _iter = MAPTABLE.find(name);
        _iter.value().value = QString::number(value);
        _iter.value().bValChanged = true;
    } else {
        _VALUE_ELEMENT4JSON_MAP element;
        QString key = name;
        while (name.contains(".")) {
            int DotIndex = name.indexOf(".");
            if (DotIndex != -1) {
                name = name.mid(DotIndex + 1);
            }
        }
        element.name = name;
        element.value = QString::number(value);
        element.valType = J4_FLOAT64_MAP;
        element.bValChanged = true;
        MAPTABLE.insert(key, element);
    }
    return b_ret;
}

bool JsonParse2Map::setParameter(QString name, unsigned int& value) {
  bool b_ret = MAPTABLE.contains(name);
  if (b_ret) {
    QMap<QString, _VALUE_ELEMENT4JSON_MAP>::iterator _iter;
    _iter = MAPTABLE.find(name);
    _iter.value().value = QString::number(value);
    _iter.value().bValChanged = true;
  } else {
    _VALUE_ELEMENT4JSON_MAP element;
    QString key = name;
    while (name.contains(".")) {
      int DotIndex = name.indexOf(".");
      if (DotIndex != -1) {
        name = name.mid(DotIndex + 1);
      }
    }
    element.name = name;
    element.value = QString::number(value);
    element.valType = J4_FLOAT64_MAP;
    element.bValChanged = true;
    MAPTABLE.insert(key, element);
  }
  return b_ret;
}

bool JsonParse2Map::setParameter(QString name, QString& value)
{
    bool b_ret = MAPTABLE.contains(name);
    if (b_ret) {
        QMap<QString, _VALUE_ELEMENT4JSON_MAP>::iterator _iter;
        _iter = MAPTABLE.find(name);
        _iter.value().value = value;
        _iter.value().bValChanged = true;
    } else {
        _VALUE_ELEMENT4JSON_MAP element;
        QString key = name;
        while (name.contains(".")) {
            int DotIndex = name.indexOf(".");
            if (DotIndex != -1) {
                name = name.mid(DotIndex + 1);
            }
        }
        element.name = name;
        element.value = value;
        element.valType = J4_QSTRING_MAP;
        element.bValChanged = true;
        MAPTABLE.insert(key, element);
    }
    return b_ret;
}

bool JsonParse2Map::getParameter(QString name, double& value)
{
    bool b_ret = MAPTABLE.contains(name);
    if (b_ret) {
        QMap<QString, _VALUE_ELEMENT4JSON_MAP>::iterator _iter;
        _iter = MAPTABLE.find(name);
        value = _iter.value().value.toDouble(&b_ret);
    } else {
//        log_singleton::Write_Log("获取Json参数错误", Log_Level::Urgent);
//        qDebug() << "获取Json参数错误" << name;
    }
    return b_ret;
}

bool JsonParse2Map::getParameter(QString name, QString& value)
{
    bool b_ret = MAPTABLE.contains(name);
    if (b_ret) {
        QMap<QString, _VALUE_ELEMENT4JSON_MAP>::iterator _iter;
        _iter = MAPTABLE.find(name);
        value = _iter.value().value;
    } else {
//        log_singleton::Write_Log("获取Json参数错误", Log_Level::Urgent);
//        qDebug() << "获取Json参数错误" << name;
    }
    return b_ret;
}

bool JsonParse2Map::getParameter(QString name, unsigned int& value)
{
    bool b_ret = MAPTABLE.contains(name);
    if (b_ret) {
        QMap<QString, _VALUE_ELEMENT4JSON_MAP>::iterator _iter;
        _iter = MAPTABLE.find(name);
        value = qRound(_iter.value().value.toDouble());
    } else {
//        log_singleton::Write_Log("获取Json参数错误", Log_Level::Urgent);
//        qDebug() << "获取Json参数错误" << name;
    }
    return b_ret;
}

bool JsonParse2Map::DeleteParameter(QString name)
{
    bool b_ret = MAPTABLE.contains(name);
    if (b_ret) {
        MAPTABLE.remove(name);
    } else {
        log_singleton::Write_Log("Json文件中不存在此元素，删除失败", Log_Level::Error);
        qDebug() << "Json文件中不存在此元素，删除失败";
    }
    return b_ret;
}

bool JsonParse2Map::DeleteParamTicket(QString name)
{
    int a1=MAPTABLE.size();
    QMap<QString,_VALUE_ELEMENT4JSON_MAP> copymap;
    for(auto it=MAPTABLE.begin();it!=MAPTABLE.end();){
        if(it.key().startsWith(name+".")){
            QString a1=it.value().name;
            qDebug()<<"****"<<a1;
            MAPTABLE.erase(it++);
        }else{
            it++;
        }
    }
    int a2=MAPTABLE.size();
    bool status=(a1==a2);
    return status;
}

void JsonParse2Map::GetValueFromRecipe(QString KeyWord,
    QList<Key2Value>& ParamsList)
{
    if (!ParamsList.isEmpty())
        ParamsList.clear();
    qint8 knum=KeyWord.size();
    for (auto it = MAPTABLE.constBegin(); it != MAPTABLE.constEnd(); ++it) {
        if(it.key().startsWith(KeyWord+"."))
        {
            Key2Value singlevalue;
            singlevalue.Name = it.value().name;
            singlevalue.Value = it.value().value.toDouble();
            ParamsList.append(singlevalue);
        }
    }
}

void JsonParse2Map::SetValue2Recipe(QString KeyWord,
    QList<Key2Value>& ParamList)
{
    for (int i = 0; i < ParamList.count(); i++) {
        QString key = KeyWord + "." + ParamList[i].Name;
        setParameter(key, ParamList[i].Value);
    }

}

void JsonParse2Map::GetValueFromRecipes(QStringList KeyWord, QList<QList<Key2Value> > &ParamAll)
{
    if(ParamAll.size()!=0){
        ParamAll.clear();
    }

    for(const QString& keyw : KeyWord){
        QList<Key2Value> paramList;
        for(auto j=MAPTABLE.constBegin();j!=MAPTABLE.constEnd();j++){
            if(j.key().startsWith(keyw+".")){
                Key2Value sigvalue;
                sigvalue.Name=j.value().name;
                bool ok;
                double value = j.value().value.toDouble(&ok);
                if (!ok) {
                    qWarning() << "Failed to convert value to double";
                    continue;
                }
                sigvalue.Value=value;
                paramList.append(sigvalue);
            }
        }
        ParamAll.append(paramList);
    }
//    qDebug()<<"Para.size:"<<ParamAll.size()<<"KeyWord.size"<<KeyWord.size();
//    for(int i=0;i<ParamAll.size();i++){
//        if(!ParamAll[i].isEmpty()){
//            qDebug()<<"aaa";
//        }
//        for(int j=0;j<ParamAll[i].size();j++){
//            qDebug()<<"ParamAll"<<ParamAll[i][j].Name<<ParamAll[i][j].Value;
//        }
//    }
}

void JsonParse2Map::SetValue2Recipes(QStringList KeyWord, QList<QList<Key2Value> > &ParamAll)
{
    for(auto i=0;i<KeyWord.size();i++){
        for(int j=0;j<ParamAll[i].count();j++){
            QString key=KeyWord[i]+"."+ParamAll[i][j].Name;
            //qDebug()<<"key"<<key<<
            setParameter(key,ParamAll[i][j].Value);
        }
    }
}


int JsonParse2Map::ParseJsonFile(QString FileName)
{
    QFile file(FileName);
    file.open(QIODevice::ReadOnly);
    if (!file.isOpen()) {
        log_singleton::Write_Log("文件打开错误: " + FileName, Log_Level::Error);
        qDebug() << "文件打开错误";
        return -1;
    }
    QString jsonString = QString(file.readAll());//json文件的全部内容(qstring)
    file.close();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonString.toUtf8());
    if (jsonDocument.isNull()) {
        log_singleton::Write_Log("Json文件读取错误", Log_Level::Error);
        qDebug() << "Json文件读取错误";
        return -1;
    }
    ParseJsonObject(jsonDocument.object());//解析json文件数据
    log_singleton::Write_Log("已读取文件:" + FileName, Log_Level::General);
    qDebug()<<"已读取文件:"<<FileName;
    return 0;
}

//解析数据
void JsonParse2Map::ParseJsonObject(const QJsonObject& jsonObj)
{
    for (auto it = jsonObj.constBegin(); it != jsonObj.constEnd(); ++it) {
        CurrentKey += it.key();
        QJsonValue currentValue = it.value();
        if (currentValue.isObject()) {//当前值是一个对象，则继续递归调用
            CurrentKey += ".";
            ParseJsonObject(currentValue.toObject());
            CurrentKey.chop(it.key().length() + 1);
        } else {
            _VALUE_ELEMENT4JSON_MAP element;
            element.name = it.key();
            if (currentValue.isDouble()) {
                double LastValue = currentValue.toDouble();
                element.value = QString::number(LastValue);
                element.valType = J4_FLOAT64_MAP;
            } else if (currentValue.isString()) {
                QString LastValue = currentValue.toString();
                element.value = LastValue;
                element.valType = J4_QSTRING_MAP;
            }
            MAPTABLE.insert(CurrentKey, element); //至此为止参数全部写入Hash表
            CurrentKey.chop(it.key().length());
        }
    }
//    qDebug()<<MAPTABLE.size();
//    for(auto i=MAPTABLE.constBegin();i!=MAPTABLE.constEnd();i++){
//        qDebug()<<"key"<<i.key()<<"name"<<i.value().name;
//    }
}

int JsonParse2Map::CountValuesUnderKey(const QString& key) const
{
    int count = 0;
    QSet<QString> firstKeys;
    for (auto it = MAPTABLE.constBegin(); it != MAPTABLE.constEnd(); ++it) {
        QString currentKey = it.key();
        if (currentKey == key) {
            count++;
        } else if (currentKey.startsWith(key + ".")) {
            int firstDotIndex = currentKey.indexOf('.', key.length() + 1);
            if (firstDotIndex != -1) {
                QString firstSubKey = currentKey.mid(key.length() + 1, firstDotIndex - key.length() - 1);
                if (!firstKeys.contains(firstSubKey)) {
                    count++;
                    firstKeys.insert(firstSubKey);
                }
            }
        }
    }
    return count;
}

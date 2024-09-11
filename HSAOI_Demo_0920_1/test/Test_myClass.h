#ifndef TEST_MYCLASS_H
#define TEST_MYCLASS_H

#include <QObject>
#include <QTest>

class Test_myClass:public QObject
{
    Q_OBJECT
private slots:
    void Test(){
        QCOMPARE(1,1);
    }
};

#endif // TEST_MYCLASS_H

#ifndef TEST_MYCLASS_H
#define TEST_MYCLASS_H

#include <QObject>
#include <QTest>

class Test_myClass:public QObject
{
    Q_OBJECT
private slots:
    void Test1(){
        QCOMPARE(1,1);
    }
    void Test2(){
        QCOMPARE(1,2);
    }
};

#endif // TEST_MYCLASS_H

#include <QCoreApplication>
#include <QDebug>
#include "Test_myClass.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    int status = QTest::qExec(new Test_myClass());
    if (status == 0) {
        qDebug() << "All tests passed!";
    } else {
        qDebug() << "Some tests failed!";
    }

    return a.exec();
}

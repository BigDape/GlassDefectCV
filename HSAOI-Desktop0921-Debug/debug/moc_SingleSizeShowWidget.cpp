/****************************************************************************
** Meta object code from reading C++ file 'SingleSizeShowWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../HSAOI_Demo_0920_1/Form/SingleSizeShowWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SingleSizeShowWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SingleSizeShowWidget_t {
    QByteArrayData data[11];
    char stringdata0[160];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SingleSizeShowWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SingleSizeShowWidget_t qt_meta_stringdata_SingleSizeShowWidget = {
    {
QT_MOC_LITERAL(0, 0, 20), // "SingleSizeShowWidget"
QT_MOC_LITERAL(1, 21, 14), // "slot_RecieveID"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 12), // "jsonFullPath"
QT_MOC_LITERAL(4, 50, 7), // "glassid"
QT_MOC_LITERAL(5, 58, 23), // "slot_showSizeSmallImage"
QT_MOC_LITERAL(6, 82, 17), // "QTableWidgetItem*"
QT_MOC_LITERAL(7, 100, 4), // "item"
QT_MOC_LITERAL(8, 105, 24), // "slot_onItemDoubleClicked"
QT_MOC_LITERAL(9, 130, 16), // "slot_refreshSize"
QT_MOC_LITERAL(10, 147, 12) // "jsonFilePath"

    },
    "SingleSizeShowWidget\0slot_RecieveID\0"
    "\0jsonFullPath\0glassid\0slot_showSizeSmallImage\0"
    "QTableWidgetItem*\0item\0slot_onItemDoubleClicked\0"
    "slot_refreshSize\0jsonFilePath"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SingleSizeShowWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   34,    2, 0x0a /* Public */,
       5,    1,   39,    2, 0x0a /* Public */,
       8,    1,   42,    2, 0x0a /* Public */,
       9,    2,   45,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   10,    4,

       0        // eod
};

void SingleSizeShowWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SingleSizeShowWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slot_RecieveID((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->slot_showSizeSmallImage((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 2: _t->slot_onItemDoubleClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 3: _t->slot_refreshSize((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SingleSizeShowWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_SingleSizeShowWidget.data,
    qt_meta_data_SingleSizeShowWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SingleSizeShowWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SingleSizeShowWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SingleSizeShowWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int SingleSizeShowWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

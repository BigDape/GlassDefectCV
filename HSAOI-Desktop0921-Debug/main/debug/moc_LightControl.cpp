/****************************************************************************
** Meta object code from reading C++ file 'LightControl.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../HSAOI_Demo_0920_1/main/LightControl/LightControl.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LightControl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_LightControl_t {
    QByteArrayData data[12];
    char stringdata0[182];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LightControl_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LightControl_t qt_meta_stringdata_LightControl = {
    {
QT_MOC_LITERAL(0, 0, 12), // "LightControl"
QT_MOC_LITERAL(1, 13, 22), // "slot_getButton_clicked"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 22), // "slot_setButton_clicked"
QT_MOC_LITERAL(4, 60, 23), // "slot_saveButton_clicked"
QT_MOC_LITERAL(5, 84, 19), // "onItemDoubleClicked"
QT_MOC_LITERAL(6, 104, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(7, 121, 4), // "item"
QT_MOC_LITERAL(8, 126, 6), // "column"
QT_MOC_LITERAL(9, 133, 13), // "slot_InitTree"
QT_MOC_LITERAL(10, 147, 18), // "on_Trigger_clicked"
QT_MOC_LITERAL(11, 166, 15) // "slot_updateCode"

    },
    "LightControl\0slot_getButton_clicked\0"
    "\0slot_setButton_clicked\0slot_saveButton_clicked\0"
    "onItemDoubleClicked\0QTreeWidgetItem*\0"
    "item\0column\0slot_InitTree\0on_Trigger_clicked\0"
    "slot_updateCode"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LightControl[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x08 /* Private */,
       3,    0,   50,    2, 0x08 /* Private */,
       4,    0,   51,    2, 0x08 /* Private */,
       5,    2,   52,    2, 0x08 /* Private */,
       9,    0,   57,    2, 0x08 /* Private */,
      10,    0,   58,    2, 0x08 /* Private */,
      11,    0,   59,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6, QMetaType::Int,    7,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void LightControl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LightControl *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slot_getButton_clicked(); break;
        case 1: _t->slot_setButton_clicked(); break;
        case 2: _t->slot_saveButton_clicked(); break;
        case 3: _t->onItemDoubleClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->slot_InitTree(); break;
        case 5: _t->on_Trigger_clicked(); break;
        case 6: _t->slot_updateCode(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject LightControl::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_LightControl.data,
    qt_meta_data_LightControl,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *LightControl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LightControl::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LightControl.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int LightControl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

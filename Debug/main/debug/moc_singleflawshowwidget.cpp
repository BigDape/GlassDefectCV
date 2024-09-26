/****************************************************************************
** Meta object code from reading C++ file 'singleflawshowwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../HSAOI_Demo_0920_1/main/Form/singleflawshowwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'singleflawshowwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SingleFlawShowWidget_t {
    QByteArrayData data[15];
    char stringdata0[194];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SingleFlawShowWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SingleFlawShowWidget_t qt_meta_stringdata_SingleFlawShowWidget = {
    {
QT_MOC_LITERAL(0, 0, 20), // "SingleFlawShowWidget"
QT_MOC_LITERAL(1, 21, 18), // "sig_paintFlawPoint"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 1), // "x"
QT_MOC_LITERAL(4, 43, 1), // "y"
QT_MOC_LITERAL(5, 45, 13), // "showFlawImage"
QT_MOC_LITERAL(6, 59, 17), // "QTableWidgetItem*"
QT_MOC_LITERAL(7, 77, 4), // "item"
QT_MOC_LITERAL(8, 82, 19), // "onItemDoubleClicked"
QT_MOC_LITERAL(9, 102, 14), // "slot_RecieveID"
QT_MOC_LITERAL(10, 117, 12), // "jsonFullPath"
QT_MOC_LITERAL(11, 130, 7), // "glassid"
QT_MOC_LITERAL(12, 138, 14), // "slot_FlawTrack"
QT_MOC_LITERAL(13, 153, 24), // "slot_ButtonExportClicked"
QT_MOC_LITERAL(14, 178, 15) // "slot_refrshFlaw"

    },
    "SingleFlawShowWidget\0sig_paintFlawPoint\0"
    "\0x\0y\0showFlawImage\0QTableWidgetItem*\0"
    "item\0onItemDoubleClicked\0slot_RecieveID\0"
    "jsonFullPath\0glassid\0slot_FlawTrack\0"
    "slot_ButtonExportClicked\0slot_refrshFlaw"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SingleFlawShowWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   54,    2, 0x0a /* Public */,
       8,    1,   57,    2, 0x0a /* Public */,
       9,    2,   60,    2, 0x0a /* Public */,
      12,    1,   65,    2, 0x0a /* Public */,
      13,    0,   68,    2, 0x0a /* Public */,
      14,    2,   69,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   10,   11,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   10,   11,

       0        // eod
};

void SingleFlawShowWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SingleFlawShowWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sig_paintFlawPoint((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->showFlawImage((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 2: _t->onItemDoubleClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 3: _t->slot_RecieveID((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->slot_FlawTrack((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 5: _t->slot_ButtonExportClicked(); break;
        case 6: _t->slot_refrshFlaw((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SingleFlawShowWidget::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SingleFlawShowWidget::sig_paintFlawPoint)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SingleFlawShowWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_SingleFlawShowWidget.data,
    qt_meta_data_SingleFlawShowWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SingleFlawShowWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SingleFlawShowWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SingleFlawShowWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int SingleFlawShowWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void SingleFlawShowWidget::sig_paintFlawPoint(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

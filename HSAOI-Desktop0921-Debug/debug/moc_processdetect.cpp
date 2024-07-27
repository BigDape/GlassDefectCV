/****************************************************************************
** Meta object code from reading C++ file 'processdetect.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../HSAOI_Demo_0920_1/ImageProcess/processdetect.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'processdetect.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Process_Detect_t {
    QByteArrayData data[19];
    char stringdata0[235];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Process_Detect_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Process_Detect_t qt_meta_stringdata_Process_Detect = {
    {
QT_MOC_LITERAL(0, 0, 14), // "Process_Detect"
QT_MOC_LITERAL(1, 15, 8), // "sendData"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 10), // "GLASSINFO*"
QT_MOC_LITERAL(4, 36, 4), // "info"
QT_MOC_LITERAL(5, 41, 14), // "sig_updateFlaw"
QT_MOC_LITERAL(6, 56, 11), // "sig_Deliver"
QT_MOC_LITERAL(7, 68, 17), // "QList<FlawPoint>*"
QT_MOC_LITERAL(8, 86, 6), // "Points"
QT_MOC_LITERAL(9, 93, 20), // "sig_UpdateResultInfo"
QT_MOC_LITERAL(10, 114, 11), // "ResultINFO*"
QT_MOC_LITERAL(11, 126, 6), // "result"
QT_MOC_LITERAL(12, 133, 17), // "sig_updateSortRes"
QT_MOC_LITERAL(13, 151, 20), // "sig_updateSignalFlaw"
QT_MOC_LITERAL(14, 172, 2), // "id"
QT_MOC_LITERAL(15, 175, 15), // "sig_refreshFlaw"
QT_MOC_LITERAL(16, 191, 7), // "glassid"
QT_MOC_LITERAL(17, 199, 15), // "sig_refreshSize"
QT_MOC_LITERAL(18, 215, 19) // "slot_updateSortInfo"

    },
    "Process_Detect\0sendData\0\0GLASSINFO*\0"
    "info\0sig_updateFlaw\0sig_Deliver\0"
    "QList<FlawPoint>*\0Points\0sig_UpdateResultInfo\0"
    "ResultINFO*\0result\0sig_updateSortRes\0"
    "sig_updateSignalFlaw\0id\0sig_refreshFlaw\0"
    "glassid\0sig_refreshSize\0slot_updateSortInfo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Process_Detect[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       5,    1,   62,    2, 0x06 /* Public */,
       6,    1,   65,    2, 0x06 /* Public */,
       9,    1,   68,    2, 0x06 /* Public */,
      12,    1,   71,    2, 0x06 /* Public */,
      13,    1,   74,    2, 0x06 /* Public */,
      15,    1,   77,    2, 0x06 /* Public */,
      17,    1,   80,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      18,    0,   83,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void Process_Detect::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Process_Detect *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendData((*reinterpret_cast< GLASSINFO*(*)>(_a[1]))); break;
        case 1: _t->sig_updateFlaw((*reinterpret_cast< GLASSINFO*(*)>(_a[1]))); break;
        case 2: _t->sig_Deliver((*reinterpret_cast< QList<FlawPoint>*(*)>(_a[1]))); break;
        case 3: _t->sig_UpdateResultInfo((*reinterpret_cast< ResultINFO*(*)>(_a[1]))); break;
        case 4: _t->sig_updateSortRes((*reinterpret_cast< ResultINFO*(*)>(_a[1]))); break;
        case 5: _t->sig_updateSignalFlaw((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->sig_refreshFlaw((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->sig_refreshSize((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->slot_updateSortInfo(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Process_Detect::*)(GLASSINFO * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Process_Detect::sendData)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Process_Detect::*)(GLASSINFO * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Process_Detect::sig_updateFlaw)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Process_Detect::*)(QList<FlawPoint> * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Process_Detect::sig_Deliver)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Process_Detect::*)(ResultINFO * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Process_Detect::sig_UpdateResultInfo)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Process_Detect::*)(ResultINFO * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Process_Detect::sig_updateSortRes)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (Process_Detect::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Process_Detect::sig_updateSignalFlaw)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (Process_Detect::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Process_Detect::sig_refreshFlaw)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (Process_Detect::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Process_Detect::sig_refreshSize)) {
                *result = 7;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Process_Detect::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Process_Detect.data,
    qt_meta_data_Process_Detect,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Process_Detect::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Process_Detect::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Process_Detect.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Process_Detect::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void Process_Detect::sendData(GLASSINFO * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Process_Detect::sig_updateFlaw(GLASSINFO * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Process_Detect::sig_Deliver(QList<FlawPoint> * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Process_Detect::sig_UpdateResultInfo(ResultINFO * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Process_Detect::sig_updateSortRes(ResultINFO * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Process_Detect::sig_updateSignalFlaw(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Process_Detect::sig_refreshFlaw(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void Process_Detect::sig_refreshSize(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

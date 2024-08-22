/****************************************************************************
** Meta object code from reading C++ file 'DushenBasicFunc.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../HSAOI_Demo_0920_1/main/Camera/Dushen/DushenBasicFunc.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DushenBasicFunc.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DushenBasicFunc_t {
    QByteArrayData data[20];
    char stringdata0[279];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DushenBasicFunc_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DushenBasicFunc_t qt_meta_stringdata_DushenBasicFunc = {
    {
QT_MOC_LITERAL(0, 0, 15), // "DushenBasicFunc"
QT_MOC_LITERAL(1, 16, 16), // "sig_DeliverImage"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 20), // "sig_DeliverFrameRate"
QT_MOC_LITERAL(4, 55, 13), // "slot_OpenFunc"
QT_MOC_LITERAL(5, 69, 10), // "DeviceName"
QT_MOC_LITERAL(6, 80, 13), // "slot_ScanFunc"
QT_MOC_LITERAL(7, 94, 14), // "slot_Closefunc"
QT_MOC_LITERAL(8, 109, 14), // "slot_StartFunc"
QT_MOC_LITERAL(9, 124, 13), // "slot_StopFunc"
QT_MOC_LITERAL(10, 138, 17), // "slot_ShowProperty"
QT_MOC_LITERAL(11, 156, 4), // "HWND"
QT_MOC_LITERAL(12, 161, 9), // "windowsID"
QT_MOC_LITERAL(13, 171, 16), // "slot_TriggerFunc"
QT_MOC_LITERAL(14, 188, 12), // "slotDispRate"
QT_MOC_LITERAL(15, 201, 13), // "slotDispImage"
QT_MOC_LITERAL(16, 215, 19), // "slot_GetCameraState"
QT_MOC_LITERAL(17, 235, 17), // "slot_SearchCamera"
QT_MOC_LITERAL(18, 253, 12), // "slot_SaveIni"
QT_MOC_LITERAL(19, 266, 12) // "slot_LoadIni"

    },
    "DushenBasicFunc\0sig_DeliverImage\0\0"
    "sig_DeliverFrameRate\0slot_OpenFunc\0"
    "DeviceName\0slot_ScanFunc\0slot_Closefunc\0"
    "slot_StartFunc\0slot_StopFunc\0"
    "slot_ShowProperty\0HWND\0windowsID\0"
    "slot_TriggerFunc\0slotDispRate\0"
    "slotDispImage\0slot_GetCameraState\0"
    "slot_SearchCamera\0slot_SaveIni\0"
    "slot_LoadIni"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DushenBasicFunc[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   89,    2, 0x06 /* Public */,
       3,    1,   92,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   95,    2, 0x08 /* Private */,
       6,    0,   98,    2, 0x0a /* Public */,
       7,    1,   99,    2, 0x0a /* Public */,
       8,    0,  102,    2, 0x0a /* Public */,
       9,    0,  103,    2, 0x0a /* Public */,
      10,    1,  104,    2, 0x0a /* Public */,
      13,    0,  107,    2, 0x0a /* Public */,
      14,    0,  108,    2, 0x0a /* Public */,
      15,    0,  109,    2, 0x0a /* Public */,
      16,    0,  110,    2, 0x0a /* Public */,
      17,    1,  111,    2, 0x0a /* Public */,
      18,    1,  114,    2, 0x0a /* Public */,
      19,    1,  117,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QImage,    2,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Bool, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool, QMetaType::QString,    5,
    QMetaType::Bool, QMetaType::QString,    5,
    QMetaType::Bool, QMetaType::QString,    5,

       0        // eod
};

void DushenBasicFunc::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DushenBasicFunc *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sig_DeliverImage((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 1: _t->sig_DeliverFrameRate((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: { bool _r = _t->slot_OpenFunc((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 3: _t->slot_ScanFunc(); break;
        case 4: _t->slot_Closefunc((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->slot_StartFunc(); break;
        case 6: _t->slot_StopFunc(); break;
        case 7: _t->slot_ShowProperty((*reinterpret_cast< HWND(*)>(_a[1]))); break;
        case 8: _t->slot_TriggerFunc(); break;
        case 9: _t->slotDispRate(); break;
        case 10: _t->slotDispImage(); break;
        case 11: _t->slot_GetCameraState(); break;
        case 12: { bool _r = _t->slot_SearchCamera((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 13: { bool _r = _t->slot_SaveIni((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 14: { bool _r = _t->slot_LoadIni((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DushenBasicFunc::*)(QImage );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DushenBasicFunc::sig_DeliverImage)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DushenBasicFunc::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DushenBasicFunc::sig_DeliverFrameRate)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DushenBasicFunc::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_DushenBasicFunc.data,
    qt_meta_data_DushenBasicFunc,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DushenBasicFunc::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DushenBasicFunc::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DushenBasicFunc.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int DushenBasicFunc::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void DushenBasicFunc::sig_DeliverImage(QImage _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DushenBasicFunc::sig_DeliverFrameRate(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

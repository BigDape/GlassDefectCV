/****************************************************************************
** Meta object code from reading C++ file 'binarylayout.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../code/log/log4qt/binarylayout.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'binarylayout.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Log4Qt__BinaryLayout_t {
    QByteArrayData data[3];
    char stringdata0[47];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Log4Qt__BinaryLayout_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Log4Qt__BinaryLayout_t qt_meta_stringdata_Log4Qt__BinaryLayout = {
    {
QT_MOC_LITERAL(0, 0, 20), // "Log4Qt::BinaryLayout"
QT_MOC_LITERAL(1, 21, 12), // "binaryFooter"
QT_MOC_LITERAL(2, 34, 12) // "binaryHeader"

    },
    "Log4Qt::BinaryLayout\0binaryFooter\0"
    "binaryHeader"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Log4Qt__BinaryLayout[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       2,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, QMetaType::QByteArray, 0x00095103,
       2, QMetaType::QByteArray, 0x00095103,

       0        // eod
};

void Log4Qt::BinaryLayout::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{

#ifndef QT_NO_PROPERTIES
    if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<BinaryLayout *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QByteArray*>(_v) = _t->binaryFooter(); break;
        case 1: *reinterpret_cast< QByteArray*>(_v) = _t->binaryHeader(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<BinaryLayout *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setBinaryFooter(*reinterpret_cast< QByteArray*>(_v)); break;
        case 1: _t->setBinaryHeader(*reinterpret_cast< QByteArray*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject Log4Qt::BinaryLayout::staticMetaObject = { {
    QMetaObject::SuperData::link<Layout::staticMetaObject>(),
    qt_meta_stringdata_Log4Qt__BinaryLayout.data,
    qt_meta_data_Log4Qt__BinaryLayout,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Log4Qt::BinaryLayout::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Log4Qt::BinaryLayout::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Log4Qt__BinaryLayout.stringdata0))
        return static_cast<void*>(this);
    return Layout::qt_metacast(_clname);
}

int Log4Qt::BinaryLayout::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Layout::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    
#ifndef QT_NO_PROPERTIES
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

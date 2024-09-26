/****************************************************************************
** Meta object code from reading C++ file 'FlawShowWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../HSAOI_Demo_0920_1/Form/FlawShowWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FlawShowWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FlawShowWidget_t {
    QByteArrayData data[25];
    char stringdata0[330];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FlawShowWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FlawShowWidget_t qt_meta_stringdata_FlawShowWidget = {
    {
QT_MOC_LITERAL(0, 0, 14), // "FlawShowWidget"
QT_MOC_LITERAL(1, 15, 21), // "sig_updatePreGlassRes"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 13), // "sig_ClearDate"
QT_MOC_LITERAL(4, 52, 17), // "sig_sendFlawPoint"
QT_MOC_LITERAL(5, 70, 9), // "FlawPoint"
QT_MOC_LITERAL(6, 80, 9), // "flawpoint"
QT_MOC_LITERAL(7, 90, 11), // "slot_resize"
QT_MOC_LITERAL(8, 102, 17), // "slot_GetGlassSize"
QT_MOC_LITERAL(9, 120, 10), // "GLASSINFO*"
QT_MOC_LITERAL(10, 131, 4), // "info"
QT_MOC_LITERAL(11, 136, 18), // "slot_GetFlawPoints"
QT_MOC_LITERAL(12, 155, 17), // "QList<FlawPoint>*"
QT_MOC_LITERAL(13, 173, 15), // "n_FlawPointList"
QT_MOC_LITERAL(14, 189, 19), // "slot_ChangeFlawShow"
QT_MOC_LITERAL(15, 209, 19), // "slot_GetGlassResult"
QT_MOC_LITERAL(16, 229, 11), // "ResultINFO*"
QT_MOC_LITERAL(17, 241, 7), // "ResInfo"
QT_MOC_LITERAL(18, 249, 23), // "slot_ButtonClearClicked"
QT_MOC_LITERAL(19, 273, 15), // "slot_PlotPicker"
QT_MOC_LITERAL(20, 289, 3), // "pos"
QT_MOC_LITERAL(21, 293, 18), // "slot_LegendChecked"
QT_MOC_LITERAL(22, 312, 8), // "itemInfo"
QT_MOC_LITERAL(23, 321, 2), // "on"
QT_MOC_LITERAL(24, 324, 5) // "index"

    },
    "FlawShowWidget\0sig_updatePreGlassRes\0"
    "\0sig_ClearDate\0sig_sendFlawPoint\0"
    "FlawPoint\0flawpoint\0slot_resize\0"
    "slot_GetGlassSize\0GLASSINFO*\0info\0"
    "slot_GetFlawPoints\0QList<FlawPoint>*\0"
    "n_FlawPointList\0slot_ChangeFlawShow\0"
    "slot_GetGlassResult\0ResultINFO*\0ResInfo\0"
    "slot_ButtonClearClicked\0slot_PlotPicker\0"
    "pos\0slot_LegendChecked\0itemInfo\0on\0"
    "index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FlawShowWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       3,    0,   72,    2, 0x06 /* Public */,
       4,    1,   73,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   76,    2, 0x0a /* Public */,
       8,    1,   77,    2, 0x0a /* Public */,
      11,    1,   80,    2, 0x0a /* Public */,
      14,    0,   83,    2, 0x0a /* Public */,
      15,    1,   84,    2, 0x0a /* Public */,
      18,    0,   87,    2, 0x0a /* Public */,
      19,    1,   88,    2, 0x0a /* Public */,
      21,    3,   91,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPointF,   20,
    QMetaType::Void, QMetaType::QVariant, QMetaType::Bool, QMetaType::Int,   22,   23,   24,

       0        // eod
};

void FlawShowWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FlawShowWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sig_updatePreGlassRes((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->sig_ClearDate(); break;
        case 2: _t->sig_sendFlawPoint((*reinterpret_cast< const FlawPoint(*)>(_a[1]))); break;
        case 3: _t->slot_resize(); break;
        case 4: _t->slot_GetGlassSize((*reinterpret_cast< GLASSINFO*(*)>(_a[1]))); break;
        case 5: _t->slot_GetFlawPoints((*reinterpret_cast< QList<FlawPoint>*(*)>(_a[1]))); break;
        case 6: _t->slot_ChangeFlawShow(); break;
        case 7: _t->slot_GetGlassResult((*reinterpret_cast< ResultINFO*(*)>(_a[1]))); break;
        case 8: _t->slot_ButtonClearClicked(); break;
        case 9: _t->slot_PlotPicker((*reinterpret_cast< const QPointF(*)>(_a[1]))); break;
        case 10: _t->slot_LegendChecked((*reinterpret_cast< const QVariant(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (FlawShowWidget::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlawShowWidget::sig_updatePreGlassRes)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (FlawShowWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlawShowWidget::sig_ClearDate)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (FlawShowWidget::*)(const FlawPoint & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlawShowWidget::sig_sendFlawPoint)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject FlawShowWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_FlawShowWidget.data,
    qt_meta_data_FlawShowWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *FlawShowWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FlawShowWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FlawShowWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int FlawShowWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void FlawShowWidget::sig_updatePreGlassRes(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FlawShowWidget::sig_ClearDate()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void FlawShowWidget::sig_sendFlawPoint(const FlawPoint & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'DushenCameraWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../code/main/Form/DushenCameraWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DushenCameraWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DushenCameraWidget_t {
    QByteArrayData data[19];
    char stringdata0[375];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DushenCameraWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DushenCameraWidget_t qt_meta_stringdata_DushenCameraWidget = {
    {
QT_MOC_LITERAL(0, 0, 18), // "DushenCameraWidget"
QT_MOC_LITERAL(1, 19, 18), // "sig_SaveCameraName"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 9), // "CameraNum"
QT_MOC_LITERAL(4, 49, 10), // "CameraName"
QT_MOC_LITERAL(5, 60, 26), // "on_pushButton_Scan_clicked"
QT_MOC_LITERAL(6, 87, 26), // "on_pushButton_Open_clicked"
QT_MOC_LITERAL(7, 114, 30), // "on_pushButton_Property_clicked"
QT_MOC_LITERAL(8, 145, 29), // "on_pushButton_trigger_clicked"
QT_MOC_LITERAL(9, 175, 6), // "status"
QT_MOC_LITERAL(10, 182, 26), // "on_pushButton_Save_clicked"
QT_MOC_LITERAL(11, 209, 29), // "on_pushButton_Saveini_clicked"
QT_MOC_LITERAL(12, 239, 29), // "on_pushButton_Loadini_clicked"
QT_MOC_LITERAL(13, 269, 38), // "on_pushButton_MultiFieldSelec..."
QT_MOC_LITERAL(14, 308, 16), // "slot_StartCamera"
QT_MOC_LITERAL(15, 325, 14), // "slot_ShowImage"
QT_MOC_LITERAL(16, 340, 5), // "image"
QT_MOC_LITERAL(17, 346, 18), // "slot_ShowFrameRate"
QT_MOC_LITERAL(18, 365, 9) // "FrameRate"

    },
    "DushenCameraWidget\0sig_SaveCameraName\0"
    "\0CameraNum\0CameraName\0on_pushButton_Scan_clicked\0"
    "on_pushButton_Open_clicked\0"
    "on_pushButton_Property_clicked\0"
    "on_pushButton_trigger_clicked\0status\0"
    "on_pushButton_Save_clicked\0"
    "on_pushButton_Saveini_clicked\0"
    "on_pushButton_Loadini_clicked\0"
    "on_pushButton_MultiFieldSelect_clicked\0"
    "slot_StartCamera\0slot_ShowImage\0image\0"
    "slot_ShowFrameRate\0FrameRate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DushenCameraWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   79,    2, 0x08 /* Private */,
       6,    0,   80,    2, 0x08 /* Private */,
       7,    0,   81,    2, 0x08 /* Private */,
       8,    1,   82,    2, 0x08 /* Private */,
      10,    0,   85,    2, 0x08 /* Private */,
      11,    0,   86,    2, 0x08 /* Private */,
      12,    0,   87,    2, 0x08 /* Private */,
      13,    0,   88,    2, 0x08 /* Private */,
      14,    0,   89,    2, 0x08 /* Private */,
      15,    1,   90,    2, 0x08 /* Private */,
      17,    1,   93,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QImage,   16,
    QMetaType::Void, QMetaType::QString,   18,

       0        // eod
};

void DushenCameraWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DushenCameraWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sig_SaveCameraName((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->on_pushButton_Scan_clicked(); break;
        case 2: _t->on_pushButton_Open_clicked(); break;
        case 3: _t->on_pushButton_Property_clicked(); break;
        case 4: _t->on_pushButton_trigger_clicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_pushButton_Save_clicked(); break;
        case 6: _t->on_pushButton_Saveini_clicked(); break;
        case 7: _t->on_pushButton_Loadini_clicked(); break;
        case 8: _t->on_pushButton_MultiFieldSelect_clicked(); break;
        case 9: _t->slot_StartCamera(); break;
        case 10: _t->slot_ShowImage((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 11: _t->slot_ShowFrameRate((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DushenCameraWidget::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DushenCameraWidget::sig_SaveCameraName)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DushenCameraWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_DushenCameraWidget.data,
    qt_meta_data_DushenCameraWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DushenCameraWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DushenCameraWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DushenCameraWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int DushenCameraWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void DushenCameraWidget::sig_SaveCameraName(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

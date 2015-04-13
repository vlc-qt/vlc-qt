/****************************************************************************
** Meta object code from reading C++ file 'EqualizerDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "EqualizerDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EqualizerDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_EqualizerDialog_t {
    QByteArrayData data[7];
    char stringdata[78];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EqualizerDialog_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EqualizerDialog_t qt_meta_stringdata_EqualizerDialog = {
    {
QT_MOC_LITERAL(0, 0, 15), // "EqualizerDialog"
QT_MOC_LITERAL(1, 16, 19), // "applyChangesForBand"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 5), // "value"
QT_MOC_LITERAL(4, 43, 19), // "applySelectedPreset"
QT_MOC_LITERAL(5, 63, 6), // "toggle"
QT_MOC_LITERAL(6, 70, 7) // "checked"

    },
    "EqualizerDialog\0applyChangesForBand\0"
    "\0value\0applySelectedPreset\0toggle\0"
    "checked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EqualizerDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x0a /* Public */,
       4,    0,   32,    2, 0x0a /* Public */,
       5,    1,   33,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    6,

       0        // eod
};

void EqualizerDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EqualizerDialog *_t = static_cast<EqualizerDialog *>(_o);
        switch (_id) {
        case 0: _t->applyChangesForBand((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->applySelectedPreset(); break;
        case 2: _t->toggle((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject EqualizerDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_EqualizerDialog.data,
      qt_meta_data_EqualizerDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *EqualizerDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EqualizerDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_EqualizerDialog.stringdata))
        return static_cast<void*>(const_cast< EqualizerDialog*>(this));
    if (!strcmp(_clname, "Ui::EqualizerDialog"))
        return static_cast< Ui::EqualizerDialog*>(const_cast< EqualizerDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int EqualizerDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

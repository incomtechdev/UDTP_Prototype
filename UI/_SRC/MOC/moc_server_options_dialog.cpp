/****************************************************************************
** Meta object code from reading C++ file 'server_options_dialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../HEADER/server_options_dialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'server_options_dialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Server_Options_dialog_t {
    QByteArrayData data[5];
    char stringdata[60];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Server_Options_dialog_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Server_Options_dialog_t qt_meta_stringdata_Server_Options_dialog = {
    {
QT_MOC_LITERAL(0, 0, 21), // "Server_Options_dialog"
QT_MOC_LITERAL(1, 22, 16), // "UserBitrateCheck"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 5), // "state"
QT_MOC_LITERAL(4, 46, 13) // "BrowseHomeDir"

    },
    "Server_Options_dialog\0UserBitrateCheck\0"
    "\0state\0BrowseHomeDir"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Server_Options_dialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x0a /* Public */,
       4,    0,   27,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,

       0        // eod
};

void Server_Options_dialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Server_Options_dialog *_t = static_cast<Server_Options_dialog *>(_o);
        switch (_id) {
        case 0: _t->UserBitrateCheck((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->BrowseHomeDir(); break;
        default: ;
        }
    }
}

const QMetaObject Server_Options_dialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Server_Options_dialog.data,
      qt_meta_data_Server_Options_dialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Server_Options_dialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Server_Options_dialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Server_Options_dialog.stringdata))
        return static_cast<void*>(const_cast< Server_Options_dialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int Server_Options_dialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'FTP_client_start.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../HEADER/FTP_client_start.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FTP_client_start.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FTP_Client_Start_dialog_t {
    QByteArrayData data[7];
    char stringdata[77];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FTP_Client_Start_dialog_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FTP_Client_Start_dialog_t qt_meta_stringdata_FTP_Client_Start_dialog = {
    {
QT_MOC_LITERAL(0, 0, 23), // "FTP_Client_Start_dialog"
QT_MOC_LITERAL(1, 24, 14), // "SetLogPathAuth"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 7), // "checked"
QT_MOC_LITERAL(4, 48, 9), // "SetIDAuth"
QT_MOC_LITERAL(5, 58, 8), // "onCancel"
QT_MOC_LITERAL(6, 67, 9) // "onConnect"

    },
    "FTP_Client_Start_dialog\0SetLogPathAuth\0"
    "\0checked\0SetIDAuth\0onCancel\0onConnect"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FTP_Client_Start_dialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x0a /* Public */,
       4,    1,   37,    2, 0x0a /* Public */,
       5,    0,   40,    2, 0x0a /* Public */,
       6,    0,   41,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void FTP_Client_Start_dialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FTP_Client_Start_dialog *_t = static_cast<FTP_Client_Start_dialog *>(_o);
        switch (_id) {
        case 0: _t->SetLogPathAuth((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->SetIDAuth((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->onCancel(); break;
        case 3: _t->onConnect(); break;
        default: ;
        }
    }
}

const QMetaObject FTP_Client_Start_dialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_FTP_Client_Start_dialog.data,
      qt_meta_data_FTP_Client_Start_dialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FTP_Client_Start_dialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FTP_Client_Start_dialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FTP_Client_Start_dialog.stringdata))
        return static_cast<void*>(const_cast< FTP_Client_Start_dialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int FTP_Client_Start_dialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE

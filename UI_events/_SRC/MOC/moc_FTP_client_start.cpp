/****************************************************************************
** Meta object code from reading C++ file 'FTP_client_start.h'
**
** Created: Tue 13. Oct 11:36:50 2015
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../HEADER/FTP_client_start.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FTP_client_start.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FTP_Client_Start_dialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      33,   25,   24,   24, 0x0a,
      54,   25,   24,   24, 0x0a,
      70,   24,   24,   24, 0x0a,
      81,   24,   24,   24, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_FTP_Client_Start_dialog[] = {
    "FTP_Client_Start_dialog\0\0checked\0"
    "SetLogPathAuth(bool)\0SetIDAuth(bool)\0"
    "onCancel()\0onConnect()\0"
};

const QMetaObject FTP_Client_Start_dialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_FTP_Client_Start_dialog,
      qt_meta_data_FTP_Client_Start_dialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FTP_Client_Start_dialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FTP_Client_Start_dialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FTP_Client_Start_dialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FTP_Client_Start_dialog))
        return static_cast<void*>(const_cast< FTP_Client_Start_dialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int FTP_Client_Start_dialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: SetLogPathAuth((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: SetIDAuth((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: onCancel(); break;
        case 3: onConnect(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
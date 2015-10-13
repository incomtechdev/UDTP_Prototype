/****************************************************************************
** Meta object code from reading C++ file 'FTP_server_thread.h'
**
** Created: Tue 13. Oct 14:59:50 2015
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../HEADER/FTP_server_thread.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FTP_server_thread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FTPServer[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   11,   10,   10, 0x05,
      44,   37,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      69,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_FTPServer[] = {
    "FTPServer\0\0message\0writeLog(QString)\0"
    "status\0setFTPServerStatus(bool)\0"
    "AbortServer()\0"
};

const QMetaObject FTPServer::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_FTPServer,
      qt_meta_data_FTPServer, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FTPServer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FTPServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FTPServer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FTPServer))
        return static_cast<void*>(const_cast< FTPServer*>(this));
    return QThread::qt_metacast(_clname);
}

int FTPServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: writeLog((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: setFTPServerStatus((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: AbortServer(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void FTPServer::writeLog(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FTPServer::setFTPServerStatus(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE

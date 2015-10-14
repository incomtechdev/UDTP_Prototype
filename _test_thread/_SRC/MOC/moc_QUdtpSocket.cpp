/****************************************************************************
** Meta object code from reading C++ file 'QUdtpSocket.h'
**
** Created: Wed 14. Oct 18:04:25 2015
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../HEADER/QUdtpSocket.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QUdtpSocket.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Udtp_thread[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,
      42,   37,   33,   12, 0x05,
      75,   68,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
     106,  102,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Udtp_thread[] = {
    "Udtp_thread\0\0deleteUdtp_thread()\0int\0"
    "data\0acceptClient(SocketData*)\0isLock\0"
    "lockClientConnection(bool)\0run\0"
    "setRunning(bool)\0"
};

const QMetaObject Udtp_thread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_Udtp_thread,
      qt_meta_data_Udtp_thread, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Udtp_thread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Udtp_thread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Udtp_thread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Udtp_thread))
        return static_cast<void*>(const_cast< Udtp_thread*>(this));
    return QThread::qt_metacast(_clname);
}

int Udtp_thread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: deleteUdtp_thread(); break;
        case 1: { int _r = acceptClient((*reinterpret_cast< SocketData*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 2: lockClientConnection((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: setRunning((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void Udtp_thread::deleteUdtp_thread()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
int Udtp_thread::acceptClient(SocketData * _t1)
{
    int _t0;
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(&_t0)), const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
    return _t0;
}

// SIGNAL 2
void Udtp_thread::lockClientConnection(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
static const uint qt_meta_data_QUdtpSocket[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   13,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      34,   12,   12,   12, 0x0a,
      63,   58,   54,   12, 0x0a,
      96,   89,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QUdtpSocket[] = {
    "QUdtpSocket\0\0run\0setRunning(bool)\0"
    "deleteUdtp_thread()\0int\0data\0"
    "acceptClient(SocketData*)\0isLock\0"
    "lockClientConnection(bool)\0"
};

const QMetaObject QUdtpSocket::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QUdtpSocket,
      qt_meta_data_QUdtpSocket, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QUdtpSocket::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QUdtpSocket::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QUdtpSocket::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QUdtpSocket))
        return static_cast<void*>(const_cast< QUdtpSocket*>(this));
    return QObject::qt_metacast(_clname);
}

int QUdtpSocket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setRunning((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: deleteUdtp_thread(); break;
        case 2: { int _r = acceptClient((*reinterpret_cast< SocketData*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: lockClientConnection((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void QUdtpSocket::setRunning(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_serverThread[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_serverThread[] = {
    "serverThread\0"
};

const QMetaObject serverThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_serverThread,
      qt_meta_data_serverThread, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &serverThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *serverThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *serverThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_serverThread))
        return static_cast<void*>(const_cast< serverThread*>(this));
    return QThread::qt_metacast(_clname);
}

int serverThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE

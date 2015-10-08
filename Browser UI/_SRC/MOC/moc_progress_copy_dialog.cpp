/****************************************************************************
** Meta object code from reading C++ file 'progress_copy_dialog.h'
**
** Created: Thu 8. Oct 15:06:42 2015
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../HEADER/progress_copy_dialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'progress_copy_dialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ClientCopyThread[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      23,   18,   17,   17, 0x05,
      46,   17,   17,   17, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_ClientCopyThread[] = {
    "ClientCopyThread\0\0size\0updateProgressBar(int)\0"
    "closeWindow()\0"
};

const QMetaObject ClientCopyThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_ClientCopyThread,
      qt_meta_data_ClientCopyThread, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ClientCopyThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ClientCopyThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ClientCopyThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ClientCopyThread))
        return static_cast<void*>(const_cast< ClientCopyThread*>(this));
    return QThread::qt_metacast(_clname);
}

int ClientCopyThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: updateProgressBar((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: closeWindow(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void ClientCopyThread::updateProgressBar(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ClientCopyThread::closeWindow()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
static const uint qt_meta_data_CopyProgress_dialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      26,   21,   20,   20, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CopyProgress_dialog[] = {
    "CopyProgress_dialog\0\0size\0"
    "UpdateProgressBar(int)\0"
};

const QMetaObject CopyProgress_dialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CopyProgress_dialog,
      qt_meta_data_CopyProgress_dialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CopyProgress_dialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CopyProgress_dialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CopyProgress_dialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CopyProgress_dialog))
        return static_cast<void*>(const_cast< CopyProgress_dialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int CopyProgress_dialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: UpdateProgressBar((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

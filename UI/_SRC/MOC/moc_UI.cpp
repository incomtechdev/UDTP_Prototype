/****************************************************************************
** Meta object code from reading C++ file 'UI.h'
**
** Created: Thu 8. Oct 15:06:42 2015
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../HEADER/UI.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'UI.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_UI[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
       4,    3,    3,    3, 0x05,

 // slots: signature, parameters, type, tag, flags
      25,   18,    3,    3, 0x0a,
      58,   50,    3,    3, 0x0a,
      88,   83,    3,    3, 0x0a,
     131,   83,    3,    3, 0x0a,
     172,  166,    3,    3, 0x0a,
     193,  166,    3,    3, 0x0a,
     223,  215,    3,    3, 0x0a,
     244,    3,    3,    3, 0x2a,
     261,  215,    3,    3, 0x0a,
     285,    3,    3,    3, 0x2a,
     305,  215,    3,    3, 0x0a,
     329,    3,    3,    3, 0x2a,
     349,  215,    3,    3, 0x0a,
     373,    3,    3,    3, 0x2a,

       0        // eod
};

static const char qt_meta_stringdata_UI[] = {
    "UI\0\0abortServer()\0status\0"
    "SetFTPServerStatus(bool)\0message\0"
    "WriteLogMessage(QString)\0item\0"
    "changeDirFromFileSystem(QTableWidgetItem*)\0"
    "SetWorkingPanel(QTableWidgetItem*)\0"
    "index\0ChangeLeftDrive(int)\0"
    "ChangeRightDrive(int)\0checked\0"
    "StartFTPServer(bool)\0StartFTPServer()\0"
    "OpenServerOptions(bool)\0OpenServerOptions()\0"
    "OpenClientOptions(bool)\0OpenClientOptions()\0"
    "OpenViewerOptions(bool)\0OpenViewerOptions()\0"
};

const QMetaObject UI::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_UI,
      qt_meta_data_UI, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &UI::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *UI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *UI::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UI))
        return static_cast<void*>(const_cast< UI*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int UI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: abortServer(); break;
        case 1: SetFTPServerStatus((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: WriteLogMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: changeDirFromFileSystem((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 4: SetWorkingPanel((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 5: ChangeLeftDrive((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: ChangeRightDrive((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: StartFTPServer((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: StartFTPServer(); break;
        case 9: OpenServerOptions((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: OpenServerOptions(); break;
        case 11: OpenClientOptions((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: OpenClientOptions(); break;
        case 13: OpenViewerOptions((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: OpenViewerOptions(); break;
        default: ;
        }
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void UI::abortServer()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE

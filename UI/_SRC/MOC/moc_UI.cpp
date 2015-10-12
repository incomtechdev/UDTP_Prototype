/****************************************************************************
** Meta object code from reading C++ file 'UI.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../HEADER/UI.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'UI.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_UI_t {
    QByteArrayData data[20];
    char stringdata[260];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UI_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UI_t qt_meta_stringdata_UI = {
    {
QT_MOC_LITERAL(0, 0, 2), // "UI"
QT_MOC_LITERAL(1, 3, 11), // "abortServer"
QT_MOC_LITERAL(2, 15, 0), // ""
QT_MOC_LITERAL(3, 16, 18), // "SetFTPServerStatus"
QT_MOC_LITERAL(4, 35, 6), // "status"
QT_MOC_LITERAL(5, 42, 15), // "WriteLogMessage"
QT_MOC_LITERAL(6, 58, 7), // "message"
QT_MOC_LITERAL(7, 66, 23), // "changeDirFromFileSystem"
QT_MOC_LITERAL(8, 90, 17), // "QTableWidgetItem*"
QT_MOC_LITERAL(9, 108, 4), // "item"
QT_MOC_LITERAL(10, 113, 15), // "SetWorkingPanel"
QT_MOC_LITERAL(11, 129, 15), // "ChangeLeftDrive"
QT_MOC_LITERAL(12, 145, 5), // "index"
QT_MOC_LITERAL(13, 151, 16), // "ChangeRightDrive"
QT_MOC_LITERAL(14, 168, 14), // "StartFTPServer"
QT_MOC_LITERAL(15, 183, 7), // "checked"
QT_MOC_LITERAL(16, 191, 14), // "StartFTPClient"
QT_MOC_LITERAL(17, 206, 17), // "OpenServerOptions"
QT_MOC_LITERAL(18, 224, 17), // "OpenClientOptions"
QT_MOC_LITERAL(19, 242, 17) // "OpenViewerOptions"

    },
    "UI\0abortServer\0\0SetFTPServerStatus\0"
    "status\0WriteLogMessage\0message\0"
    "changeDirFromFileSystem\0QTableWidgetItem*\0"
    "item\0SetWorkingPanel\0ChangeLeftDrive\0"
    "index\0ChangeRightDrive\0StartFTPServer\0"
    "checked\0StartFTPClient\0OpenServerOptions\0"
    "OpenClientOptions\0OpenViewerOptions"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UI[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   99,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,  100,    2, 0x0a /* Public */,
       5,    1,  103,    2, 0x0a /* Public */,
       7,    1,  106,    2, 0x0a /* Public */,
      10,    1,  109,    2, 0x0a /* Public */,
      11,    1,  112,    2, 0x0a /* Public */,
      13,    1,  115,    2, 0x0a /* Public */,
      14,    1,  118,    2, 0x0a /* Public */,
      14,    0,  121,    2, 0x2a /* Public | MethodCloned */,
      16,    1,  122,    2, 0x0a /* Public */,
      16,    0,  125,    2, 0x2a /* Public | MethodCloned */,
      17,    1,  126,    2, 0x0a /* Public */,
      17,    0,  129,    2, 0x2a /* Public | MethodCloned */,
      18,    1,  130,    2, 0x0a /* Public */,
      18,    0,  133,    2, 0x2a /* Public | MethodCloned */,
      19,    1,  134,    2, 0x0a /* Public */,
      19,    0,  137,    2, 0x2a /* Public | MethodCloned */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Bool,   15,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   15,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   15,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   15,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   15,
    QMetaType::Void,

       0        // eod
};

void UI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UI *_t = static_cast<UI *>(_o);
        switch (_id) {
        case 0: _t->abortServer(); break;
        case 1: _t->SetFTPServerStatus((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->WriteLogMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->changeDirFromFileSystem((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 4: _t->SetWorkingPanel((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 5: _t->ChangeLeftDrive((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->ChangeRightDrive((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->StartFTPServer((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->StartFTPServer(); break;
        case 9: _t->StartFTPClient((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->StartFTPClient(); break;
        case 11: _t->OpenServerOptions((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->OpenServerOptions(); break;
        case 13: _t->OpenClientOptions((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: _t->OpenClientOptions(); break;
        case 15: _t->OpenViewerOptions((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 16: _t->OpenViewerOptions(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (UI::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UI::abortServer)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject UI::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_UI.data,
      qt_meta_data_UI,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *UI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UI::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_UI.stringdata))
        return static_cast<void*>(const_cast< UI*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int UI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void UI::abortServer()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE

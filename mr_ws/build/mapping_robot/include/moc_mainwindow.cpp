/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/mapping_robot/include/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[17];
    char stringdata0[320];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 21), // "startSensorBtnClicked"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 20), // "stopSensorBtnClicked"
QT_MOC_LITERAL(4, 55, 21), // "startRecordBtnClicked"
QT_MOC_LITERAL(5, 77, 20), // "stopRecordBtnClicked"
QT_MOC_LITERAL(6, 98, 19), // "parseDataBtnClicked"
QT_MOC_LITERAL(7, 118, 25), // "on_startSensorBtn_clicked"
QT_MOC_LITERAL(8, 144, 24), // "on_stopSensorBtn_clicked"
QT_MOC_LITERAL(9, 169, 25), // "on_startRecordBtn_clicked"
QT_MOC_LITERAL(10, 195, 24), // "on_stopRecordBtn_clicked"
QT_MOC_LITERAL(11, 220, 23), // "on_parseDataBtn_clicked"
QT_MOC_LITERAL(12, 244, 15), // "startSensorDone"
QT_MOC_LITERAL(13, 260, 14), // "stopSensorDone"
QT_MOC_LITERAL(14, 275, 15), // "startRecordDone"
QT_MOC_LITERAL(15, 291, 14), // "stopRecordDone"
QT_MOC_LITERAL(16, 306, 13) // "parseDataDone"

    },
    "MainWindow\0startSensorBtnClicked\0\0"
    "stopSensorBtnClicked\0startRecordBtnClicked\0"
    "stopRecordBtnClicked\0parseDataBtnClicked\0"
    "on_startSensorBtn_clicked\0"
    "on_stopSensorBtn_clicked\0"
    "on_startRecordBtn_clicked\0"
    "on_stopRecordBtn_clicked\0"
    "on_parseDataBtn_clicked\0startSensorDone\0"
    "stopSensorDone\0startRecordDone\0"
    "stopRecordDone\0parseDataDone"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x06 /* Public */,
       3,    0,   90,    2, 0x06 /* Public */,
       4,    0,   91,    2, 0x06 /* Public */,
       5,    0,   92,    2, 0x06 /* Public */,
       6,    1,   93,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   96,    2, 0x0a /* Public */,
       8,    0,   97,    2, 0x0a /* Public */,
       9,    0,   98,    2, 0x0a /* Public */,
      10,    0,   99,    2, 0x0a /* Public */,
      11,    0,  100,    2, 0x0a /* Public */,
      12,    0,  101,    2, 0x0a /* Public */,
      13,    0,  102,    2, 0x0a /* Public */,
      14,    0,  103,    2, 0x0a /* Public */,
      15,    0,  104,    2, 0x0a /* Public */,
      16,    0,  105,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->startSensorBtnClicked(); break;
        case 1: _t->stopSensorBtnClicked(); break;
        case 2: _t->startRecordBtnClicked(); break;
        case 3: _t->stopRecordBtnClicked(); break;
        case 4: _t->parseDataBtnClicked((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->on_startSensorBtn_clicked(); break;
        case 6: _t->on_stopSensorBtn_clicked(); break;
        case 7: _t->on_startRecordBtn_clicked(); break;
        case 8: _t->on_stopRecordBtn_clicked(); break;
        case 9: _t->on_parseDataBtn_clicked(); break;
        case 10: _t->startSensorDone(); break;
        case 11: _t->stopSensorDone(); break;
        case 12: _t->startRecordDone(); break;
        case 13: _t->stopRecordDone(); break;
        case 14: _t->parseDataDone(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::startSensorBtnClicked)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::stopSensorBtnClicked)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::startRecordBtnClicked)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::stopRecordBtnClicked)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::parseDataBtnClicked)) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::startSensorBtnClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MainWindow::stopSensorBtnClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MainWindow::startRecordBtnClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void MainWindow::stopRecordBtnClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void MainWindow::parseDataBtnClicked(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
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
    QByteArrayData data[19];
    char stringdata0[322];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 8), // "readData"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 8), // "escribir"
QT_MOC_LITERAL(4, 30, 11), // "const char*"
QT_MOC_LITERAL(5, 42, 5), // "datos"
QT_MOC_LITERAL(6, 48, 14), // "escribirCadena"
QT_MOC_LITERAL(7, 63, 25), // "on_btnDesconectar_pressed"
QT_MOC_LITERAL(8, 89, 22), // "on_btnConectar_pressed"
QT_MOC_LITERAL(9, 112, 43), // "on_cmbSerialPortSelector_curr..."
QT_MOC_LITERAL(10, 156, 4), // "arg1"
QT_MOC_LITERAL(11, 161, 44), // "on_cmbSerialPortSelector_curr..."
QT_MOC_LITERAL(12, 206, 5), // "index"
QT_MOC_LITERAL(13, 212, 23), // "ControlRobotDiferencial"
QT_MOC_LITERAL(14, 236, 2), // "dx"
QT_MOC_LITERAL(15, 239, 2), // "dy"
QT_MOC_LITERAL(16, 242, 13), // "EnviarComando"
QT_MOC_LITERAL(17, 256, 28), // "on_btnParoEmergencia_pressed"
QT_MOC_LITERAL(18, 285, 36) // "on_cmbSerialPortSelector_high..."

    },
    "MainWindow\0readData\0\0escribir\0const char*\0"
    "datos\0escribirCadena\0on_btnDesconectar_pressed\0"
    "on_btnConectar_pressed\0"
    "on_cmbSerialPortSelector_currentTextChanged\0"
    "arg1\0on_cmbSerialPortSelector_currentIndexChanged\0"
    "index\0ControlRobotDiferencial\0dx\0dy\0"
    "EnviarComando\0on_btnParoEmergencia_pressed\0"
    "on_cmbSerialPortSelector_highlighted"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x08 /* Private */,
       3,    1,   70,    2, 0x08 /* Private */,
       6,    1,   73,    2, 0x08 /* Private */,
       7,    0,   76,    2, 0x08 /* Private */,
       8,    0,   77,    2, 0x08 /* Private */,
       9,    1,   78,    2, 0x08 /* Private */,
      11,    1,   81,    2, 0x08 /* Private */,
      13,    2,   84,    2, 0x08 /* Private */,
      16,    0,   89,    2, 0x08 /* Private */,
      17,    0,   90,    2, 0x08 /* Private */,
      18,    1,   91,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, QMetaType::QByteArray,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::SChar, QMetaType::SChar,   14,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   12,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->readData(); break;
        case 1: _t->escribir((*reinterpret_cast< const char*(*)>(_a[1]))); break;
        case 2: _t->escribirCadena((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 3: _t->on_btnDesconectar_pressed(); break;
        case 4: _t->on_btnConectar_pressed(); break;
        case 5: _t->on_cmbSerialPortSelector_currentTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->on_cmbSerialPortSelector_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->ControlRobotDiferencial((*reinterpret_cast< signed char(*)>(_a[1])),(*reinterpret_cast< signed char(*)>(_a[2]))); break;
        case 8: _t->EnviarComando(); break;
        case 9: _t->on_btnParoEmergencia_pressed(); break;
        case 10: _t->on_cmbSerialPortSelector_highlighted((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
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
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

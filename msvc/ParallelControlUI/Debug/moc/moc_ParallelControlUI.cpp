/****************************************************************************
** Meta object code from reading C++ file 'ParallelControlUI.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../ParallelControlUI.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ParallelControlUI.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ParallelControlUI_t {
    QByteArrayData data[14];
    char stringdata0[233];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ParallelControlUI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ParallelControlUI_t qt_meta_stringdata_ParallelControlUI = {
    {
QT_MOC_LITERAL(0, 0, 17), // "ParallelControlUI"
QT_MOC_LITERAL(1, 18, 17), // "SginalOnConnected"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 20), // "SginalOnDisconnected"
QT_MOC_LITERAL(4, 58, 18), // "SignalOnRspMovePos"
QT_MOC_LITERAL(5, 77, 15), // "ST_RspMove_POS*"
QT_MOC_LITERAL(6, 93, 3), // "rsp"
QT_MOC_LITERAL(7, 97, 18), // "SignalOnRspMoveVel"
QT_MOC_LITERAL(8, 116, 15), // "ST_RspMove_VEL*"
QT_MOC_LITERAL(9, 132, 19), // "slot_btn_calc_click"
QT_MOC_LITERAL(10, 152, 17), // "slot_on_connected"
QT_MOC_LITERAL(11, 170, 20), // "slot_on_disconnected"
QT_MOC_LITERAL(12, 191, 20), // "slot_on_rsp_move_pos"
QT_MOC_LITERAL(13, 212, 20) // "slot_on_rsp_move_vel"

    },
    "ParallelControlUI\0SginalOnConnected\0"
    "\0SginalOnDisconnected\0SignalOnRspMovePos\0"
    "ST_RspMove_POS*\0rsp\0SignalOnRspMoveVel\0"
    "ST_RspMove_VEL*\0slot_btn_calc_click\0"
    "slot_on_connected\0slot_on_disconnected\0"
    "slot_on_rsp_move_pos\0slot_on_rsp_move_vel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ParallelControlUI[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x06 /* Public */,
       3,    0,   60,    2, 0x06 /* Public */,
       4,    1,   61,    2, 0x06 /* Public */,
       7,    1,   64,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   67,    2, 0x0a /* Public */,
      10,    0,   68,    2, 0x0a /* Public */,
      11,    0,   69,    2, 0x0a /* Public */,
      12,    1,   70,    2, 0x0a /* Public */,
      13,    1,   73,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 8,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 8,    6,

       0        // eod
};

void ParallelControlUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ParallelControlUI *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SginalOnConnected(); break;
        case 1: _t->SginalOnDisconnected(); break;
        case 2: _t->SignalOnRspMovePos((*reinterpret_cast< ST_RspMove_POS*(*)>(_a[1]))); break;
        case 3: _t->SignalOnRspMoveVel((*reinterpret_cast< ST_RspMove_VEL*(*)>(_a[1]))); break;
        case 4: _t->slot_btn_calc_click(); break;
        case 5: _t->slot_on_connected(); break;
        case 6: _t->slot_on_disconnected(); break;
        case 7: _t->slot_on_rsp_move_pos((*reinterpret_cast< ST_RspMove_POS*(*)>(_a[1]))); break;
        case 8: _t->slot_on_rsp_move_vel((*reinterpret_cast< ST_RspMove_VEL*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ParallelControlUI::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ParallelControlUI::SginalOnConnected)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ParallelControlUI::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ParallelControlUI::SginalOnDisconnected)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ParallelControlUI::*)(ST_RspMove_POS * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ParallelControlUI::SignalOnRspMovePos)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ParallelControlUI::*)(ST_RspMove_VEL * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ParallelControlUI::SignalOnRspMoveVel)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ParallelControlUI::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_ParallelControlUI.data,
    qt_meta_data_ParallelControlUI,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ParallelControlUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ParallelControlUI::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ParallelControlUI.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int ParallelControlUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void ParallelControlUI::SginalOnConnected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ParallelControlUI::SginalOnDisconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ParallelControlUI::SignalOnRspMovePos(ST_RspMove_POS * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ParallelControlUI::SignalOnRspMoveVel(ST_RspMove_VEL * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

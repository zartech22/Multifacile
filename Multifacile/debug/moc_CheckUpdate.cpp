/****************************************************************************
** Meta object code from reading C++ file 'CheckUpdate.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../CheckUpdate.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CheckUpdate.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CheckUpdate[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      43,   12,   12,   12, 0x0a,
      58,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CheckUpdate[] = {
    "CheckUpdate\0\0checkUpdateAnswer(UpdateType)\0"
    "dataReceived()\0sendRequest()\0"
};

void CheckUpdate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CheckUpdate *_t = static_cast<CheckUpdate *>(_o);
        switch (_id) {
        case 0: _t->checkUpdateAnswer((*reinterpret_cast< UpdateType(*)>(_a[1]))); break;
        case 1: _t->dataReceived(); break;
        case 2: _t->sendRequest(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CheckUpdate::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CheckUpdate::staticMetaObject = {
    { &QTcpSocket::staticMetaObject, qt_meta_stringdata_CheckUpdate,
      qt_meta_data_CheckUpdate, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CheckUpdate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CheckUpdate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CheckUpdate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CheckUpdate))
        return static_cast<void*>(const_cast< CheckUpdate*>(this));
    return QTcpSocket::qt_metacast(_clname);
}

int CheckUpdate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTcpSocket::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void CheckUpdate::checkUpdateAnswer(UpdateType _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE

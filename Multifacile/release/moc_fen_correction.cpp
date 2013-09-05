/****************************************************************************
** Meta object code from reading C++ file 'fen_correction.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../fen_correction.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fen_correction.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Fen_correction[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   16,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Fen_correction[] = {
    "Fen_correction\0\0,\0openMessageBox(RecordState,int)\0"
};

void Fen_correction::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Fen_correction *_t = static_cast<Fen_correction *>(_o);
        switch (_id) {
        case 0: _t->openMessageBox((*reinterpret_cast< RecordState(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Fen_correction::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Fen_correction::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Fen_correction,
      qt_meta_data_Fen_correction, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Fen_correction::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Fen_correction::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Fen_correction::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Fen_correction))
        return static_cast<void*>(const_cast< Fen_correction*>(this));
    return QWidget::qt_metacast(_clname);
}

int Fen_correction::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

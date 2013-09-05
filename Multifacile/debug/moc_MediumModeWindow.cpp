/****************************************************************************
** Meta object code from reading C++ file 'MediumModeWindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../MediumModeWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MediumModeWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MediumModeWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x05,
      34,   17,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
      46,   17,   17,   17, 0x0a,
      56,   17,   17,   17, 0x0a,
      75,   68,   17,   17, 0x0a,
      92,   17,   17,   17, 0x0a,
      99,   17,   17,   17, 0x0a,
     110,   17,   17,   17, 0x0a,
     118,   17,   17,   17, 0x0a,
     147,  141,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MediumModeWindow[] = {
    "MediumModeWindow\0\0addSeconde(int)\0"
    "wasClosed()\0correct()\0newSecond()\0"
    "number\0newSetFocus(int)\0Next()\0"
    "Previous()\0Retry()\0showEvent(QShowEvent*)\0"
    "temps\0updateLabel(int)\0"
};

void MediumModeWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MediumModeWindow *_t = static_cast<MediumModeWindow *>(_o);
        switch (_id) {
        case 0: _t->addSeconde((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->wasClosed(); break;
        case 2: _t->correct(); break;
        case 3: _t->newSecond(); break;
        case 4: _t->newSetFocus((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 5: _t->Next(); break;
        case 6: _t->Previous(); break;
        case 7: _t->Retry(); break;
        case 8: _t->showEvent((*reinterpret_cast< QShowEvent*(*)>(_a[1]))); break;
        case 9: _t->updateLabel((*reinterpret_cast< const int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MediumModeWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MediumModeWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MediumModeWindow,
      qt_meta_data_MediumModeWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MediumModeWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MediumModeWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MediumModeWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MediumModeWindow))
        return static_cast<void*>(const_cast< MediumModeWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int MediumModeWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void MediumModeWindow::addSeconde(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MediumModeWindow::wasClosed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'fenetre_principale.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../fenetre_principale.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fenetre_principale.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Fenetre_principale[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x0a,
      38,   34,   19,   19, 0x0a,
      62,   55,   19,   19, 0x0a,
     100,   19,   19,   19, 0x0a,
     115,   19,   19,   19, 0x0a,
     137,  130,   19,   19, 0x0a,
     155,  130,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Fenetre_principale[] = {
    "Fenetre_principale\0\0open_window()\0nbr\0"
    "open_window(int)\0update\0"
    "checkUpdateReceivedAnswer(UpdateType)\0"
    "erreurSocket()\0verification()\0action\0"
    "setMode(QAction*)\0resetLabel(QAction*)\0"
};

void Fenetre_principale::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Fenetre_principale *_t = static_cast<Fenetre_principale *>(_o);
        switch (_id) {
        case 0: _t->open_window(); break;
        case 1: _t->open_window((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 2: _t->checkUpdateReceivedAnswer((*reinterpret_cast< UpdateType(*)>(_a[1]))); break;
        case 3: _t->erreurSocket(); break;
        case 4: _t->verification(); break;
        case 5: _t->setMode((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 6: _t->resetLabel((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Fenetre_principale::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Fenetre_principale::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Fenetre_principale,
      qt_meta_data_Fenetre_principale, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Fenetre_principale::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Fenetre_principale::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Fenetre_principale::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Fenetre_principale))
        return static_cast<void*>(const_cast< Fenetre_principale*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Fenetre_principale::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

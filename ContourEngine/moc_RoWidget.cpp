/****************************************************************************
** Meta object code from reading C++ file 'RoWidget_2.h'
**
** Created: Wed Aug 5 09:55:58 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "RoWidget_2.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RoWidget_2.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CRoWidget[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x0a,
      20,   10,   10,   10, 0x0a,
      30,   10,   10,   10, 0x0a,
      41,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CRoWidget[] = {
    "CRoWidget\0\0ZoomIn()\0ZoomOut()\0RotateUp()\0"
    "RotateDown()\0"
};

const QMetaObject CRoWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CRoWidget,
      qt_meta_data_CRoWidget, 0 }
};

const QMetaObject *CRoWidget::metaObject() const
{
    return &staticMetaObject;
}

void *CRoWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CRoWidget))
        return static_cast<void*>(const_cast< CRoWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int CRoWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: ZoomIn(); break;
        case 1: ZoomOut(); break;
        case 2: RotateUp(); break;
        case 3: RotateDown(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

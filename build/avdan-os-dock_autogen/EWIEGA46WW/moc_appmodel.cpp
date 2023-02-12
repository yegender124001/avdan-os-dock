/****************************************************************************
** Meta object code from reading C++ file 'appmodel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../appmodel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'appmodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AppModel_t {
    QByteArrayData data[18];
    char stringdata0[140];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AppModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AppModel_t qt_meta_stringdata_AppModel = {
    {
QT_MOC_LITERAL(0, 0, 8), // "AppModel"
QT_MOC_LITERAL(1, 9, 12), // "countChanged"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 9), // "itemAdded"
QT_MOC_LITERAL(4, 33, 11), // "itemRemoved"
QT_MOC_LITERAL(5, 45, 4), // "save"
QT_MOC_LITERAL(6, 50, 7), // "clicked"
QT_MOC_LITERAL(7, 58, 2), // "id"
QT_MOC_LITERAL(8, 61, 11), // "raiseWindow"
QT_MOC_LITERAL(9, 73, 15), // "openNewInstance"
QT_MOC_LITERAL(10, 89, 5), // "appId"
QT_MOC_LITERAL(11, 95, 3), // "pin"
QT_MOC_LITERAL(12, 99, 5), // "unPin"
QT_MOC_LITERAL(13, 105, 16), // "updateGeometries"
QT_MOC_LITERAL(14, 122, 4), // "rect"
QT_MOC_LITERAL(15, 127, 4), // "move"
QT_MOC_LITERAL(16, 132, 4), // "from"
QT_MOC_LITERAL(17, 137, 2) // "to"

    },
    "AppModel\0countChanged\0\0itemAdded\0"
    "itemRemoved\0save\0clicked\0id\0raiseWindow\0"
    "openNewInstance\0appId\0pin\0unPin\0"
    "updateGeometries\0rect\0move\0from\0to"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AppModel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,
       3,    0,   70,    2, 0x06 /* Public */,
       4,    0,   71,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
       5,    0,   72,    2, 0x02 /* Public */,
       6,    1,   73,    2, 0x02 /* Public */,
       8,    1,   76,    2, 0x02 /* Public */,
       9,    1,   79,    2, 0x02 /* Public */,
      11,    1,   82,    2, 0x02 /* Public */,
      12,    1,   85,    2, 0x02 /* Public */,
      13,    2,   88,    2, 0x02 /* Public */,
      15,    2,   93,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Bool, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::QString, QMetaType::QRect,    7,   14,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   16,   17,

       0        // eod
};

void AppModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AppModel *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->countChanged(); break;
        case 1: _t->itemAdded(); break;
        case 2: _t->itemRemoved(); break;
        case 3: _t->save(); break;
        case 4: _t->clicked((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->raiseWindow((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: { bool _r = _t->openNewInstance((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 7: _t->pin((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->unPin((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->updateGeometries((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< QRect(*)>(_a[2]))); break;
        case 10: _t->move((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AppModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AppModel::countChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (AppModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AppModel::itemAdded)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (AppModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AppModel::itemRemoved)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject AppModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QAbstractListModel::staticMetaObject>(),
    qt_meta_stringdata_AppModel.data,
    qt_meta_data_AppModel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *AppModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AppModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AppModel.stringdata0))
        return static_cast<void*>(this);
    return QAbstractListModel::qt_metacast(_clname);
}

int AppModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void AppModel::countChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void AppModel::itemAdded()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void AppModel::itemRemoved()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

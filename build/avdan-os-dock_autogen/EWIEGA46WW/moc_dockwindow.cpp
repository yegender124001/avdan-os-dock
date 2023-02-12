/****************************************************************************
** Meta object code from reading C++ file 'dockwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../dockwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dockwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DockWindow_t {
    QByteArrayData data[12];
    char stringdata0[141];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DockWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DockWindow_t qt_meta_stringdata_DockWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "DockWindow"
QT_MOC_LITERAL(1, 11, 17), // "windowBlurChanged"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 19), // "windowRadiusChanged"
QT_MOC_LITERAL(4, 50, 12), // "enableStruts"
QT_MOC_LITERAL(5, 63, 10), // "updateBlur"
QT_MOC_LITERAL(6, 74, 15), // "setWindowRadius"
QT_MOC_LITERAL(7, 90, 6), // "radius"
QT_MOC_LITERAL(8, 97, 13), // "setWindowBlur"
QT_MOC_LITERAL(9, 111, 5), // "value"
QT_MOC_LITERAL(10, 117, 12), // "windowRadius"
QT_MOC_LITERAL(11, 130, 10) // "windowBlur"

    },
    "DockWindow\0windowBlurChanged\0\0"
    "windowRadiusChanged\0enableStruts\0"
    "updateBlur\0setWindowRadius\0radius\0"
    "setWindowBlur\0value\0windowRadius\0"
    "windowBlur"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DockWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       2,   54, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    0,   45,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   46,    2, 0x0a /* Public */,
       5,    0,   47,    2, 0x0a /* Public */,
       6,    1,   48,    2, 0x0a /* Public */,
       8,    1,   51,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Bool,    9,

 // properties: name, type, flags
      10, QMetaType::Int, 0x00495103,
      11, QMetaType::Bool, 0x00495103,

 // properties: notify_signal_id
       1,
       0,

       0        // eod
};

void DockWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DockWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->windowBlurChanged(); break;
        case 1: _t->windowRadiusChanged(); break;
        case 2: _t->enableStruts(); break;
        case 3: _t->updateBlur(); break;
        case 4: _t->setWindowRadius((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->setWindowBlur((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DockWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DockWindow::windowBlurChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DockWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DockWindow::windowRadiusChanged)) {
                *result = 1;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<DockWindow *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->windowRadius(); break;
        case 1: *reinterpret_cast< bool*>(_v) = _t->windowBlur(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<DockWindow *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setWindowRadius(*reinterpret_cast< int*>(_v)); break;
        case 1: _t->setWindowBlur(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject DockWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QQuickWindow::staticMetaObject>(),
    qt_meta_stringdata_DockWindow.data,
    qt_meta_data_DockWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DockWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DockWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DockWindow.stringdata0))
        return static_cast<void*>(this);
    return QQuickWindow::qt_metacast(_clname);
}

int DockWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QQuickWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void DockWindow::windowBlurChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void DockWindow::windowRadiusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

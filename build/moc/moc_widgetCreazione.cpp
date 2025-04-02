/****************************************************************************
** Meta object code from reading C++ file 'widgetCreazione.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../src/grafica/widgetCreazione.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widgetCreazione.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_widgetCreazione_t {
    uint offsetsAndSizes[16];
    char stringdata0[16];
    char stringdata1[5];
    char stringdata2[1];
    char stringdata3[12];
    char stringdata4[12];
    char stringdata5[7];
    char stringdata6[9];
    char stringdata7[7];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_widgetCreazione_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_widgetCreazione_t qt_meta_stringdata_widgetCreazione = {
    {
        QT_MOC_LITERAL(0, 15),  // "widgetCreazione"
        QT_MOC_LITERAL(16, 4),  // "crea"
        QT_MOC_LITERAL(21, 0),  // ""
        QT_MOC_LITERAL(22, 11),  // "browseImage"
        QT_MOC_LITERAL(34, 11),  // "buildWidget"
        QT_MOC_LITERAL(46, 6),  // "libro*"
        QT_MOC_LITERAL(53, 8),  // "canzone*"
        QT_MOC_LITERAL(62, 6)   // "album*"
    },
    "widgetCreazione",
    "crea",
    "",
    "browseImage",
    "buildWidget",
    "libro*",
    "canzone*",
    "album*"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_widgetCreazione[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   44,    2, 0x0a,    1 /* Public */,
       3,    0,   45,    2, 0x0a,    2 /* Public */,
       4,    1,   46,    2, 0x0a,    3 /* Public */,
       4,    1,   49,    2, 0x0a,    5 /* Public */,
       4,    1,   52,    2, 0x0a,    7 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void, 0x80000000 | 7,    2,

       0        // eod
};

Q_CONSTINIT const QMetaObject widgetCreazione::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_widgetCreazione.offsetsAndSizes,
    qt_meta_data_widgetCreazione,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_widgetCreazione_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<widgetCreazione, std::true_type>,
        // method 'crea'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'browseImage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'buildWidget'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<libro *, std::false_type>,
        // method 'buildWidget'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<canzone *, std::false_type>,
        // method 'buildWidget'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<album *, std::false_type>
    >,
    nullptr
} };

void widgetCreazione::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<widgetCreazione *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->crea(); break;
        case 1: _t->browseImage(); break;
        case 2: _t->buildWidget((*reinterpret_cast< std::add_pointer_t<libro*>>(_a[1]))); break;
        case 3: _t->buildWidget((*reinterpret_cast< std::add_pointer_t<canzone*>>(_a[1]))); break;
        case 4: _t->buildWidget((*reinterpret_cast< std::add_pointer_t<album*>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *widgetCreazione::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *widgetCreazione::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_widgetCreazione.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int widgetCreazione::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

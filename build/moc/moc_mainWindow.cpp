/****************************************************************************
** Meta object code from reading C++ file 'mainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../src/grafica/mainWindow.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainWindow.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_mainWindow_t {
    uint offsetsAndSizes[22];
    char stringdata0[11];
    char stringdata1[12];
    char stringdata2[1];
    char stringdata3[20];
    char stringdata4[19];
    char stringdata5[8];
    char stringdata6[20];
    char stringdata7[16];
    char stringdata8[10];
    char stringdata9[12];
    char stringdata10[10];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_mainWindow_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_mainWindow_t qt_meta_stringdata_mainWindow = {
    {
        QT_MOC_LITERAL(0, 10),  // "mainWindow"
        QT_MOC_LITERAL(11, 11),  // "browseImage"
        QT_MOC_LITERAL(23, 0),  // ""
        QT_MOC_LITERAL(24, 19),  // "confermaSalvataggio"
        QT_MOC_LITERAL(44, 18),  // "annullaSalvataggio"
        QT_MOC_LITERAL(63, 7),  // "ricerca"
        QT_MOC_LITERAL(71, 19),  // "reloadMediaVisibili"
        QT_MOC_LITERAL(91, 15),  // "sceltaCreazione"
        QT_MOC_LITERAL(107, 9),  // "creaLibro"
        QT_MOC_LITERAL(117, 11),  // "creaCanzone"
        QT_MOC_LITERAL(129, 9)   // "creaAlbum"
    },
    "mainWindow",
    "browseImage",
    "",
    "confermaSalvataggio",
    "annullaSalvataggio",
    "ricerca",
    "reloadMediaVisibili",
    "sceltaCreazione",
    "creaLibro",
    "creaCanzone",
    "creaAlbum"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_mainWindow[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   68,    2, 0x08,    1 /* Private */,
       3,    0,   69,    2, 0x08,    2 /* Private */,
       4,    0,   70,    2, 0x08,    3 /* Private */,
       5,    0,   71,    2, 0x0a,    4 /* Public */,
       6,    0,   72,    2, 0x0a,    5 /* Public */,
       7,    0,   73,    2, 0x0a,    6 /* Public */,
       8,    0,   74,    2, 0x0a,    7 /* Public */,
       9,    0,   75,    2, 0x0a,    8 /* Public */,
      10,    0,   76,    2, 0x0a,    9 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject mainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_mainWindow.offsetsAndSizes,
    qt_meta_data_mainWindow,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_mainWindow_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<mainWindow, std::true_type>,
        // method 'browseImage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'confermaSalvataggio'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'annullaSalvataggio'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'ricerca'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'reloadMediaVisibili'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sceltaCreazione'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'creaLibro'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'creaCanzone'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'creaAlbum'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void mainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<mainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->browseImage(); break;
        case 1: _t->confermaSalvataggio(); break;
        case 2: _t->annullaSalvataggio(); break;
        case 3: _t->ricerca(); break;
        case 4: _t->reloadMediaVisibili(); break;
        case 5: _t->sceltaCreazione(); break;
        case 6: _t->creaLibro(); break;
        case 7: _t->creaCanzone(); break;
        case 8: _t->creaAlbum(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *mainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *mainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_mainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int mainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

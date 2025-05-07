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
    uint offsetsAndSizes[20];
    char stringdata0[11];
    char stringdata1[16];
    char stringdata2[1];
    char stringdata3[20];
    char stringdata4[22];
    char stringdata5[20];
    char stringdata6[12];
    char stringdata7[14];
    char stringdata8[12];
    char stringdata9[20];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_mainWindow_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_mainWindow_t qt_meta_stringdata_mainWindow = {
    {
        QT_MOC_LITERAL(0, 10),  // "mainWindow"
        QT_MOC_LITERAL(11, 15),  // "sceltaCreazione"
        QT_MOC_LITERAL(27, 0),  // ""
        QT_MOC_LITERAL(28, 19),  // "avviaCreazioneLibro"
        QT_MOC_LITERAL(48, 21),  // "avviaCreazioneCanzone"
        QT_MOC_LITERAL(70, 19),  // "avviaCreazioneAlbum"
        QT_MOC_LITERAL(90, 11),  // "filtraLibri"
        QT_MOC_LITERAL(102, 13),  // "filtraCanzoni"
        QT_MOC_LITERAL(116, 11),  // "filtraAlbum"
        QT_MOC_LITERAL(128, 19)   // "reloadAreaContenuti"
    },
    "mainWindow",
    "sceltaCreazione",
    "",
    "avviaCreazioneLibro",
    "avviaCreazioneCanzone",
    "avviaCreazioneAlbum",
    "filtraLibri",
    "filtraCanzoni",
    "filtraAlbum",
    "reloadAreaContenuti"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_mainWindow[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   62,    2, 0x08,    1 /* Private */,
       3,    0,   63,    2, 0x08,    2 /* Private */,
       4,    0,   64,    2, 0x08,    3 /* Private */,
       5,    0,   65,    2, 0x08,    4 /* Private */,
       6,    0,   66,    2, 0x08,    5 /* Private */,
       7,    0,   67,    2, 0x08,    6 /* Private */,
       8,    0,   68,    2, 0x08,    7 /* Private */,
       9,    0,   69,    2, 0x0a,    8 /* Public */,

 // slots: parameters
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
        // method 'sceltaCreazione'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'avviaCreazioneLibro'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'avviaCreazioneCanzone'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'avviaCreazioneAlbum'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'filtraLibri'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'filtraCanzoni'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'filtraAlbum'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'reloadAreaContenuti'
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
        case 0: _t->sceltaCreazione(); break;
        case 1: _t->avviaCreazioneLibro(); break;
        case 2: _t->avviaCreazioneCanzone(); break;
        case 3: _t->avviaCreazioneAlbum(); break;
        case 4: _t->filtraLibri(); break;
        case 5: _t->filtraCanzoni(); break;
        case 6: _t->filtraAlbum(); break;
        case 7: _t->reloadAreaContenuti(); break;
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
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

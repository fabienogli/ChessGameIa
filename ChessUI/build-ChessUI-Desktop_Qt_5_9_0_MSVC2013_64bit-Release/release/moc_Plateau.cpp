/****************************************************************************
** Meta object code from reading C++ file 'Plateau.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Chess/Chess/Plateau.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Plateau.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Plateau_t {
    QByteArrayData data[25];
    char stringdata0[187];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Plateau_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Plateau_t qt_meta_stringdata_Plateau = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Plateau"
QT_MOC_LITERAL(1, 8, 14), // "affichSuppInit"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 6), // "Piece*"
QT_MOC_LITERAL(4, 31, 5), // "piece"
QT_MOC_LITERAL(5, 37, 2), // "id"
QT_MOC_LITERAL(6, 40, 1), // "i"
QT_MOC_LITERAL(7, 42, 15), // "displayPlayerId"
QT_MOC_LITERAL(8, 58, 7), // "badMove"
QT_MOC_LITERAL(9, 66, 10), // "loseSignal"
QT_MOC_LITERAL(10, 77, 8), // "coupJoue"
QT_MOC_LITERAL(11, 86, 8), // "idjoueur"
QT_MOC_LITERAL(12, 95, 4), // "xDep"
QT_MOC_LITERAL(13, 100, 4), // "yDep"
QT_MOC_LITERAL(14, 105, 4), // "xArr"
QT_MOC_LITERAL(15, 110, 4), // "yArr"
QT_MOC_LITERAL(16, 115, 8), // "setLevel"
QT_MOC_LITERAL(17, 124, 5), // "level"
QT_MOC_LITERAL(18, 130, 19), // "sentDisplayPlayerId"
QT_MOC_LITERAL(19, 150, 14), // "displayPlateau"
QT_MOC_LITERAL(20, 165, 9), // "movePiece"
QT_MOC_LITERAL(21, 175, 2), // "i1"
QT_MOC_LITERAL(22, 178, 2), // "i2"
QT_MOC_LITERAL(23, 181, 2), // "i3"
QT_MOC_LITERAL(24, 184, 2) // "i4"

    },
    "Plateau\0affichSuppInit\0\0Piece*\0piece\0"
    "id\0i\0displayPlayerId\0badMove\0loseSignal\0"
    "coupJoue\0idjoueur\0xDep\0yDep\0xArr\0yArr\0"
    "setLevel\0level\0sentDisplayPlayerId\0"
    "displayPlateau\0movePiece\0i1\0i2\0i3\0i4"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Plateau[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   59,    2, 0x06 /* Public */,
       7,    1,   66,    2, 0x06 /* Public */,
       8,    0,   69,    2, 0x06 /* Public */,
       9,    0,   70,    2, 0x06 /* Public */,
      10,    5,   71,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      16,    1,   82,    2, 0x0a /* Public */,
      18,    0,   85,    2, 0x0a /* Public */,
      19,    0,   86,    2, 0x0a /* Public */,
      20,    4,   87,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int, QMetaType::Int,    4,    5,    6,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   11,   12,   13,   14,   15,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,   17,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   21,   22,   23,   24,

       0        // eod
};

void Plateau::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Plateau *_t = static_cast<Plateau *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->affichSuppInit((*reinterpret_cast< Piece*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: _t->displayPlayerId((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->badMove(); break;
        case 3: _t->loseSignal(); break;
        case 4: _t->coupJoue((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 5: _t->setLevel((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->sentDisplayPlayerId(); break;
        case 7: _t->displayPlateau(); break;
        case 8: _t->movePiece((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Plateau::*_t)(Piece * , int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Plateau::affichSuppInit)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Plateau::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Plateau::displayPlayerId)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Plateau::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Plateau::badMove)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (Plateau::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Plateau::loseSignal)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (Plateau::*_t)(int , int , int , int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Plateau::coupJoue)) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject Plateau::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Plateau.data,
      qt_meta_data_Plateau,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Plateau::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Plateau::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Plateau.stringdata0))
        return static_cast<void*>(const_cast< Plateau*>(this));
    return QObject::qt_metacast(_clname);
}

int Plateau::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void Plateau::affichSuppInit(Piece * _t1, int _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Plateau::displayPlayerId(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Plateau::badMove()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Plateau::loseSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Plateau::coupJoue(int _t1, int _t2, int _t3, int _t4, int _t5)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

TEMPLATE = lib
CONFIG += console
CONFIG += staticlib
CONFIG -= app_bundle
CONFIG -= qt

DEFINES -= UNICODE

QMAKE_CXXFLAGS += -std=gnu++11
QMAKE_LFLAGS += -Wl,--exclude-all-symbols

INCLUDEPATH += "C:/Projects/pcx"

SOURCES += \
    optional.cpp \
    process.cpp

HEADERS += \
    flags.h \
    aligned_store.h \
    non_copyable.h \
    str.h \
    any.h \
    lexical_cast.h \
    optional.h \
    ptr_vector.h \
    range_reverse.h \
    join_str.h \
    scoped_ptr.h \
    signals.h \
    process.h

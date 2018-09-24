TEMPLATE = lib
CONFIG += console
CONFIG += staticlib
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=gnu++11
QMAKE_LFLAGS += -Wl,--exclude-all-symbols

SOURCES += \
    pcx.cpp \
    optional.cpp

HEADERS += \
    flags.h \
    aligned_store.h \
    non_copyable.h \
    str.h \
    any.h \
    lexical_cast.h \
    optional.h \
    ptr_vector.h \
    range_reverse.h

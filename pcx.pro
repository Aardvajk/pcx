TEMPLATE = lib
CONFIG += console
CONFIG += staticlib
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=gnu++11
QMAKE_LFLAGS += -Wl,--exclude-all-symbols

SOURCES += \
    pcx.cpp

HEADERS += \
    flags.h \
    aligned_store.h

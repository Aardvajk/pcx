TEMPLATE = lib
CONFIG += console
CONFIG += staticlib
CONFIG -= app_bundle
CONFIG -= qt

DEFINES -= UNICODE
INCLUDEPATH += C:/wclang/include

LIBS += -L"C:/wclang/lib"

INCLUDEPATH += "C:/Projects/pcx"

SOURCES += \
    args.cpp \
    base64.cpp \
    filesys.cpp \
    format.cpp \
    optional.cpp \
    process.cpp \
    scoped_lock.cpp \
    datastream.cpp \
    split_str.cpp \
    textfile.cpp

HEADERS += \
    args.h \
    base64.h \
    callback.h \
    filesys.h \
    flags.h \
    aligned_store.h \
    format.h \
    indexed_set.h \
    non_copyable.h \
    shared_ptr.h \
    str.h \
    any.h \
    lexical_cast.h \
    optional.h \
    ptr_vector.h \
    range_reverse.h \
    join_str.h \
    scoped_ptr.h \
    signals.h \
    process.h \
    scoped_lock.h \
    ordered_map.h \
    shared_data.h \
    resource_map.h \
    enum_range.h \
    indexed_range.h \
    datastream.h \
    fixed_array.h \
    buffer.h \
    split_str.h \
    scoped_counter.h \
    scoped_push.h \
    textfile.h

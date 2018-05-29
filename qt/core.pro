#-------------------------------------------------
#
# Project created by QtCreator 2016-06-03T13:43:38
#
#-------------------------------------------------

QT       -= core gui

TARGET = core
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    ../src/object.cpp \
    ../src/stream.cpp \
    ../src/buffer.cpp \
    ../src/func.cpp \
    ../src/list.cpp \
    ../src/strings.cpp \
    ../src/utf.cpp

HEADERS += \
    ../src/core.h \
    ../src/object.h \
    ../src/stream.h \
    ../src/types.h \
    ../src/buffer.h \
    ../src/cfg.h \
    ../src/func.h \
    ../src/list.h \
    ../src/strings.h \
    ../src/utf.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

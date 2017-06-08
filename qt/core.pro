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
    ../src/application.cpp \
    ../src/logger.cpp \
    ../src/object.cpp \
    ../src/stream.cpp \
    ../src/config.cpp \
    ../src/buffer.cpp \
    ../src/func.cpp \
    ../src/list.cpp \
    ../src/registry.cpp \
    ../src/strings.cpp \
    ../src/utf.cpp \
    ../src/xmlParser.cpp

HEADERS += \
    ../src/application.h \
    ../src/core.h \
    ../src/logger.h \
    ../src/object.h \
    ../src/stream.h \
    ../src/types.h \
    ../src/config.h \
    ../src/buffer.h \
    ../src/cfg.h \
    ../src/func.h \
    ../src/list.h \
    ../src/registry.h \
    ../src/strings.h \
    ../src/utf.h \
    ../src/xmlParser.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

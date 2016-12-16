#-------------------------------------------------
#
# Project created by QtCreator 2016-06-03T13:43:38
#
#-------------------------------------------------

QT       -= core gui

TARGET = cjCore
TEMPLATE = lib
CONFIG += c++14 staticlib

SOURCES += \
    ../src/application.cpp \
    ../src/cjcore.cpp \
    ../src/config.cpp \
    ../src/func.cpp \
    ../src/list.cpp \
    ../src/logger.cpp \
    ../src/object.cpp \
    ../src/registry.cpp \
    ../src/stream.cpp \
    ../src/strings.cpp \
    ../src/test_utf32to8.cpp \
    ../src/utf.cpp \
    ../src/xmlParser.cpp

HEADERS += \
    ../src/application.h \
    ../src/cfg.h \
    ../src/cj.h \
    ../src/cjcore.h \
    ../src/config.h \
    ../src/func.h \
    ../src/list.h \
    ../src/logger.h \
    ../src/object.h \
    ../src/registry.h \
    ../src/stream.h \
    ../src/strings.h \
    ../src/types.h \
    ../src/config.h \
    ../src/utf.h \
    ../src/xmlParser.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

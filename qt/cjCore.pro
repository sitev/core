#-------------------------------------------------
#
# Project created by QtCreator 2016-06-03T13:43:38
#
#-------------------------------------------------

QT       -= core gui

TARGET = cjCore
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    ../src/application.cpp \
    ../src/logger.cpp \
    ../src/object.cpp \
    ../src/stream.cpp \
    ../src/config.cpp

HEADERS += \
    ../src/application.h \
    ../src/cj.h \
    ../src/logger.h \
    ../src/object.h \
    ../src/stream.h \
    ../src/types.h \
    ../src/config.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

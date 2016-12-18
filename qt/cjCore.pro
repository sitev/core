#-------------------------------------------------
#
# Project created by QtCreator 2016-06-03T13:43:38
#
#-------------------------------------------------

QT       -= core gui

TARGET = cjCore
TEMPLATE = lib
CONFIG += c++14 staticlib

HEADERS += \
    ../src/application.h \
    ../src/cfg.h \
    ../src/cj.h \
    ../src/config.h \
    ../src/func.h \
    ../src/list.h \
    ../src/logger.h \
    ../src/object.h \
    ../src/registry.h \
    ../src/stream.h \
    ../src/strings.h \
    ../src/types.h \
    ../src/utf.h \
    ../src/xmlParser.h \
    ../src/uuid/all-io.h \
    ../src/uuid/c.h \
    ../src/uuid/randutils.h \
    ../src/uuid/uuid.h \
    ../src/uuid/uuidd.h \
    ../src/uuid/uuidP.h

SOURCES += \
    ../src/application.cpp \
    ../src/config.cpp \
    ../src/func.cpp \
    ../src/list.cpp \
    ../src/logger.cpp \
    ../src/object.cpp \
    ../src/registry.cpp \
    ../src/stream.cpp \
    ../src/strings.cpp \
    ../src/utf.cpp \
    ../src/xmlParser.cpp \
    ../src/uuid/clear.c \
    ../src/uuid/compare.c \
    ../src/uuid/copy.c \
    ../src/uuid/gen_uuid.c \
    ../src/uuid/isnull.c \
    ../src/uuid/pack.c \
    ../src/uuid/parse.c \
    ../src/uuid/randutils.c \
    ../src/uuid/test_uuid.c \
    ../src/uuid/unpack.c \
    ../src/uuid/unparse.c \
    ../src/uuid/uuid_time.c

unix {
    target.path = /usr/lib
    INSTALLS += target
}

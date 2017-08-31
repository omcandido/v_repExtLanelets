#-------------------------------------------------
#
# Project created by QtCreator 2017-08-30T11:48:36
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11

TARGET = v_repExtLanelets
TEMPLATE = lib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

*-msvc* {
    QMAKE_CXXFLAGS += -O2
    QMAKE_CXXFLAGS += -W3
}
*-g++* {
    QMAKE_CXXFLAGS += -O3
    QMAKE_CXXFLAGS += -Wall
    QMAKE_CXXFLAGS += -Wno-unused-parameter
    QMAKE_CXXFLAGS += -Wno-strict-aliasing
    QMAKE_CXXFLAGS += -Wno-empty-body
    QMAKE_CXXFLAGS += -Wno-write-strings

    QMAKE_CXXFLAGS += -Wno-unused-but-set-variable
    QMAKE_CXXFLAGS += -Wno-unused-local-typedefs
    QMAKE_CXXFLAGS += -Wno-narrowing

    QMAKE_CFLAGS += -O3
    QMAKE_CFLAGS += -Wall
    QMAKE_CFLAGS += -Wno-strict-aliasing
    QMAKE_CFLAGS += -Wno-unused-parameter
    QMAKE_CFLAGS += -Wno-unused-but-set-variable
    QMAKE_CFLAGS += -Wno-unused-local-typedefs
}

INCLUDEPATH += "../include"
INCLUDEPATH += "../common"
INCLUDEPATH += "liblanelet/installs/include"


SOURCES += \
    laneletsdialog.cpp \
    lanelet2obj.cpp \
    triangulate.cpp \
    v_repExtLanelets.cpp \

HEADERS  += \
    laneletsdialog.h \
    triangulate.h \
    v_repExtLanelets.h \

FORMS    += laneletsdialog.ui

LIBS += -L$$PWD/liblanelet/installs/lib/MRT/ -lLanelet

INCLUDEPATH += $$PWD/liblanelet/installs/include
DEPENDPATH += $$PWD/liblanelet/installs/include

CONFIG += link_pkgconfig
PKGCONFIG += geodesy

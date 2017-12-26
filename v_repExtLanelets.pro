# v_repExtLanelets plugin
# (c) Candido Otero, 2017, Universidade de Vigo
#----------------------------------------------------------


TARGET = v_repExtLanelets
TEMPLATE = lib

QT += core
QT += gui

CONFIG += c++11

INCLUDEPATH += "../include"
INCLUDEPATH += "../common"
INCLUDEPATH += "../v_repMath"

INCLUDEPATH += "dialog"
INCLUDEPATH += "triangulate"
INCLUDEPATH += "liblanelet/installs/include"

greaterThan(QT_MAJOR_VERSION,4): QT += widgets

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


win32 {
    DEFINES += WIN_VREP
}

macx {
    DEFINES += MAC_VREP
}

unix:!macx {
    DEFINES += LIN_VREP
}

SOURCES += \
    v_repExtLanelets.cpp \
    lanelet2obj.cpp \
    dialog/laneletsdialog.cpp \
    triangulate/triangulate.cpp \
    liblanelet/libLanelet/LaneletMap.cpp \
    liblanelet/libLanelet/LaneletBase.cpp \
    liblanelet/libLanelet/Attribute.cpp \
    liblanelet/libLanelet/LineStrip.cpp \
    liblanelet/libLanelet/LLTree.cpp \
    liblanelet/libLanelet/RegulatoryElement.cpp \
    liblanelet/libLanelet/CompoundLanelet.cpp \
    liblanelet/libLanelet/llet_xml.cpp \
    liblanelet/libLanelet/Lanelet.cpp \
    liblanelet/libpugixml/pugixml.cpp \
    ../v_repMath/3Vector.cpp \
    ../v_repMath/3X3Matrix.cpp \
    ../v_repMath/4Vector.cpp \
    ../v_repMath/4X4FullMatrix.cpp \
    ../v_repMath/4X4Matrix.cpp \
    ../v_repMath/7Vector.cpp \
    ../v_repMath/MyMath.cpp \
    ../common/v_repLib.cpp \

HEADERS +=\
    v_repExtLanelets.h \
    lanelet2obj.hpp \
    dialog/laneletsdialog.h \
    triangulate/triangulate.h \
    liblanelet/installs/include/MRT/Commons/convert_coordinates.hpp \
    liblanelet/installs/include/MRT/Commons/LocalGeographicCS.hpp \
    liblanelet/installs/include/MRT/Commons/mercator.hpp \
    liblanelet/installs/include/MRT/Commons/normalize_angle.hpp \
    liblanelet/installs/include/MRT/Commons/prettyprint.hpp \
    liblanelet/installs/include/MRT/libLanelet/Attribute.hpp \
    liblanelet/installs/include/MRT/libLanelet/LaneletFwd.hpp \
    liblanelet/installs/include/MRT/libLanelet/lanelet_point.hpp \
    liblanelet/installs/include/MRT/libLanelet/RegulatoryElement.hpp \
    liblanelet/installs/include/MRT/libLanelet/BoundingBox.hpp \
    liblanelet/installs/include/MRT/libLanelet/LaneletGraph.hpp \
    liblanelet/installs/include/MRT/libLanelet/LineStrip.hpp \
    liblanelet/installs/include/MRT/libLanelet/RTree.h \
    liblanelet/installs/include/MRT/libLanelet/CompoundLanelet.hpp \
    liblanelet/installs/include/MRT/libLanelet/Lanelet.hpp \
    liblanelet/installs/include/MRT/libLanelet/llet_xml.hpp \
    liblanelet/installs/include/MRT/libLanelet/LaneletBase.hpp \
    liblanelet/installs/include/MRT/libLanelet/LaneletMap.hpp \
    liblanelet/installs/include/MRT/libLanelet/LLTree.hpp \
    liblanelet/installs/include/MRT/libpugixml/pugiconfig.hpp \
    liblanelet/installs/include/MRT/libpugixml/pugixml.hpp \
    ../v_repMath/3Vector.h \
    ../v_repMath/3X3Matrix.h \
    ../v_repMath/4Vector.h \
    ../v_repMath/4X4FullMatrix.h \
    ../v_repMath/4X4Matrix.h \
    ../v_repMath/7Vector.h \
    ../v_repMath/MyMath.h \
    ../include/v_repLib.h \

FORMS += \
    dialog/laneletsdialog.ui

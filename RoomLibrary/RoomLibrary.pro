TEMPLATE = lib

QT -= gui
QT += quick
QT += 3dquick

CONFIG += qt plugin

TARGET = RoomLibrary

DEFINES += ROOMLIBRARY_LIBRARY

SOURCES += BasicRoom.cpp

HEADERS += BasicRoom.h

DESTDIR = ../Tepee3DEngine/libraries/room_library

OBJECTS_DIR = tmp

MOC_DIR = tmp

include(../Tepee3DEngine/DeveloperAPIFiles/DevelopmentFiles.pri)

linux {

    QMAKE_CXXFLAGS_DEBUG += -Wundef -Wunused-function -Wunused -Wmissing-declarations
    QMAKE_CXXFLAGS_RELEASE += -Wundef -Wunused-function -Wunused -Wmissing-declarations

    coverage {
        LIBS += -lgcov
        QMAKE_CXXFLAGS_DEBUG += --coverage
        QMAKE_CXXFLAGS_RELEASE += --coverage
    }
}

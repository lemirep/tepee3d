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

include(../DeveloperAPIFiles/DevelopmentFiles.pri)



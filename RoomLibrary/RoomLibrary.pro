TEMPLATE = lib

QT       -= gui
QT += quick
QT += 3dquick

CONFIG += qt plugin


TARGET = RoomLibrary


DEFINES += ROOMLIBRARY_LIBRARY

SOURCES += BasicRoom.cpp \
           ../Tepee3DSampleApp/Room/RoomBase.cpp


HEADERS += BasicRoom.h  \
           ../Tepee3DSampleApp/Room/RoomBase.h

DESTDIR = ../libraries/room_library

INCLUDEPATH += ../Tepee3DSampleApp/Room
INCLUDEPATH += ../DeveloperAPIFiles/Plugins

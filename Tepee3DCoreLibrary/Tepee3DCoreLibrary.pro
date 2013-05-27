TEMPLATE = lib

QT += qml
QT += quick
QT += multimedia
QT += 3dquick
QT += sql

CONFIG += qt plugin

TARGET = CoreLibrary

DEFINES += CORELIBRARY_LIBRARY

DESTDIR = ../Tepee3DEngine/libraries/core

HEADERS += CoreManager.h

SOURCES += CoreManager.cpp

# Include Shared Development Files
include(../Tepee3DEngine/DeveloperAPIFiles/DevelopmentFiles.pri)
# Include QmlViewManagement
include(View/View.pri)
# Include Room Sources
include(Room/Room.pri)
# Include Services Sources
include(Services/Services.pri)
# Include Plugins Sources
include(Plugins/Plugins.pri)
# Include Platform Specific Sources
include(Platforms/Platforms.pri)


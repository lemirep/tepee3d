TEMPLATE = lib

QT       += network
QT       -= gui

CONFIG += qt plugin

TARGET = StreamManagerLibrary

DEFINES += STREAMMANAGERLIBRARY_LIBRARY

HEADERS += \
    StreamManagerLibrary.h

SOURCES += \
    StreamManagerLibrary.cpp

DESTDIR = ../../Tepee3DEngine/libraries/services_lib

INCLUDEPATH += ../../Tepee3DEngine/DeveloperAPIFiles/Services

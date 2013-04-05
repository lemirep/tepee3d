#-------------------------------------------------
#
# Project created by QtCreator 2012-10-19T03:59:26
#
#-------------------------------------------------

TEMPLATE = lib

QT       += network
QT       -= gui

CONFIG += qt plugin


TARGET = WebServiceManagerLibrary


DEFINES += WEBSERVICEMANAGERLIBRARY_LIBRARY

SOURCES += WebServiceManager.cpp \
    NetworkReplyRepeater.cpp

HEADERS += WebServiceManager.h \
    NetworkReplyRepeater.h

DESTDIR = ../../Tepee3DEngine/libraries/services_lib

INCLUDEPATH += ../../Tepee3DEngine/DeveloperAPIFiles/Services

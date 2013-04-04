#-------------------------------------------------
#
# Project created by QtCreator 2012-10-21T17:21:40
#
#-------------------------------------------------

TEMPLATE = lib

QT       += sql
QT       -= gui

CONFIG += qt plugin


TARGET = ManageDatabaseServiceLibrary


DEFINES += MANAGEDATABASELIBRARY_LIBRARY

SOURCES +=   \
    databaseThread.cpp \
    manageBDD.cpp

HEADERS +=   \
    databaseThread.h \
    manageBDD.h

DESTDIR = ../../Tepee3DEngine/libraries/services_lib

INCLUDEPATH += ../../DeveloperAPIFiles/Services

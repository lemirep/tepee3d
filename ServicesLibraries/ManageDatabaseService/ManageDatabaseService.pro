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

SOURCES +=   managebdd.cpp \
             databasethread.cpp

HEADERS +=   managebdd.h \
             databasethread.h

DESTDIR = ../../libraries/services_lib

INCLUDEPATH += ../../Tepee3DSampleApp/Services


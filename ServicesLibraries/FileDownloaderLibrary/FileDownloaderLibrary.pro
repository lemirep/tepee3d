TEMPLATE = lib

QT       += network
QT       -= gui

CONFIG += qt plugin

TARGET = FileDownloaderLibrary

DEFINES += FILEDOWNLOADERLIBRARY_LIBRARY

OBJECTS_DIR = tmp

MOC_DIR = tmp

HEADERS += \
    FileDownloaderLibrary.h \
    FileDownloadJob.h

SOURCES += \
    FileDownloaderLibrary.cpp \
    FileDownloadJob.cpp

DESTDIR = ../../Tepee3DEngine/libraries/services_lib

INCLUDEPATH += ../../Tepee3DEngine/DeveloperAPIFiles/Services

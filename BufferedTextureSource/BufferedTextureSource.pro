TEMPLATE = lib

CONFIG += qt plugin
CONFIG += release
QT += quick
QT += qml
QT += 3dquick

HEADERS += BufferedTextureSource.h \
    BufferedTextureProvider.h \
    BufferedTextureQSGTexture.h \
    BufferedTextureSourceQMLPlugin.h \
    BufferedTextureGSNode.h

SOURCES += BufferedTextureSource.cpp \
    BufferedTextureProvider.cpp \
    BufferedTextureQSGTexture.cpp \
    BufferedTextureSourceQMLPlugin.cpp \
    BufferedTextureGSNode.cpp

# DESTINATION DIRECTORY BE CAREFUL NOT TO WASTE TIME SEARCHING IT AS IT IS COPIED IN THE SHADOW BUILD DIR
DESTDIR = ../qml_extension_plugins
# NAME GIVEN TO THE GENERATED LIBRARY
TARGET = BufferedTextureSource

OTHER_FILES +=  qmldir


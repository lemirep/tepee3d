
QT += qml
QT += quick
QT += widgets
QT += 3dquick
QT += sql
QT += testlib

HEADERS += \
      TestUnit.h

SOURCES += \
    TestUnit.cpp

DESTDIR         = ../Tepee3DEngine

# Include Shared Development Files
include(../Tepee3DEngine/DeveloperAPIFiles/DevelopmentFiles.pri)
include(../Tepee3DCoreLibrary/Platforms/Platforms.pri)
include(../Tepee3DCoreLibrary/Services/Services.pri)
include(../Tepee3DCoreLibrary/Room/Room.pri)
include(../Tepee3DCoreLibrary/Plugins/Plugins.pri)
include(../Tepee3DCoreLibrary/View/View.pri)



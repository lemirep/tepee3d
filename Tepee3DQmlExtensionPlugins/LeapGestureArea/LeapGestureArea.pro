TEMPLATE = lib
CONFIG += plugin

QT += qml quick

TARGET = LeapGestureArea

OBJECTS_DIR = tmp

MOC_DIR = tmp


SOURCES += LeapGestureArea.cpp \
           LeapGestureAreaQmlExtension.cpp

HEADERS += LeapGestureArea.h \
           LeapGestureAreaQmlExtension.h

OTHER_FILES = qmldir

include (../../Tepee3DEngine/DeveloperAPIFiles/DevelopmentFiles.pri)

DESTDIR = ../../Tepee3DEngine/qml/extensions/LeapGestureArea

qmldir_install.files = $$OTHER_FILES
qmldir_install.path = $$DESTDIR

INSTALLS += qmldir_install

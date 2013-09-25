TEMPLATE = lib
CONFIG += plugin

QT += qml quick

TARGET = Tepee3DTouchArea

OBJECTS_DIR = tmp

MOC_DIR = tmp

SOURCES += Tepee3DTouchArea.cpp \
           Tepee3DTouchAreaQmlExtensionPlugin.cpp

HEADERS += Tepee3DTouchArea.h \
           Tepee3DTouchAreaQmlExtensionPlugin.h

#include (../../Tepee3DEngine/DeveloperAPIFiles/DevelopmentFiles.pri)

DESTDIR = ../../Tepee3DEngine/qml/extensions/Tepee3DTouchArea

OTHER_FILES += qmldir

qmldir_install.files = $$OTHER_FILES
qmldir_install.path = $$DESTDIR

INSTALLS += qmldir_install

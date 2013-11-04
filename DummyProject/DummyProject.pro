
TEMPLATE        = lib
CONFIG         += qt plugin
QT             += quick

 #include development files
include (DeveloperAPIFiles/DevelopmentFiles.pri)

TARGET          = DummyProject
DESTDIR         = DummyProject_Library

HEADERS += \
    DummyProject.h

SOURCES += \
    DummyProject.cpp

# QML and Resources
OTHER_FILES += \
    DummyProject.qml \
    Menu.qml


# deploy qml files to correct dir
qml_folder.files = $$OTHER_FILES
qml_folder.path = $$DESTDIR

DEPLOYMENT += qml_folder
INSTALLS += qml_folder

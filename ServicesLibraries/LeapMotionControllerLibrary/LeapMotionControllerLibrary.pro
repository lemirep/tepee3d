
TEMPLATE = lib

QT       += widgets

CONFIG += qt plugin

TARGET = LeapMotionControllerLibrary

DEFINES += LEAPMOTIONCONTROLLERLIBRARY_LIBRARY

SOURCES += LeapMotionController.cpp \
           LeapMotionListener.cpp \ 
           LeapMotionManagerLibrary.cpp

HEADERS += LeapMotionController.h \
           LeapMotionListener.h \
           LeapMotionManagerLibrary.h

DESTDIR = ../../Tepee3DEngine/libraries/services_lib

INCLUDEPATH += ../../Tepee3DEngine/DeveloperAPIFiles/Services
INCLUDEPATH += ./Leap/include

win32 {
    LIBS += ./Leap/x86/
}

win64 {
    LIBS += ./Leap/x64/
}

linux-g++-32 {
    LIBS += ./Leap/x86/libLeap.so
}

linux-g++-64 {
    LIBS += ./Leap/x64/libLeap.so
}

install_folder.files = $$LIBS
install_folder.path = ../../Tepee3DEngine/libraries/3rd_party/

INSTALLS += install_folder
DEPLOYMENT += install_folder

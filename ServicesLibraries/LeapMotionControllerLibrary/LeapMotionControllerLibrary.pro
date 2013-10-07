
TEMPLATE = lib

QT       += quick
CONFIG += qt plugin

TARGET = LeapMotionControllerLibrary

DEFINES += LEAPMOTIONCONTROLLERLIBRARY_LIBRARY

SOURCES += LeapMotionController.cpp \
           LeapMotionListener.cpp \ 
           LeapMotionManagerLibrary.cpp \
           LeapMotionTouchDevice.cpp

HEADERS += LeapMotionController.h \
           LeapMotionListener.h \
           LeapMotionManagerLibrary.h \
           LeapMotionTouchDevice.h

OBJECTS_DIR = tmp

MOC_DIR = tmp

DESTDIR = ../../Tepee3DEngine/libraries/services_lib

INCLUDEPATH += ../../Tepee3DEngine/DeveloperAPIFiles/Services
INCLUDEPATH += ../../Tepee3DEngine/DeveloperAPIFiles/View
INCLUDEPATH += ./Leap/include

win32: {
 !contains(QMAKE_HOST.arch, x86_64) {
        message("x86 build")
        LIBS += ./Leap/x86/Leap.lib
        install_folder.files += ./Leap/x86/Leap.dll
    } else {
        message("x86_64 build")

#        LIBS += ./Leap/x64/Leapd.lib
        LIBS += ./Leap/x64/Leap.lib
        install_folder.files += ./Leap/x64/Leap.dll
#        install_folder.files += ./Leap/x64/Leapd.dll
    }
}

linux-g++-32 {
    LIBS += ./Leap/x86/libLeap.so
    install_folder.files += $$LIBS
}

linux-g++-64 {
    LIBS += ./Leap/x64/libLeap.so
    install_folder.files += $$LIBS
}

install_folder.path = ../../Tepee3DEngine/libraries/3rd_party/

INSTALLS += install_folder
DEPLOYMENT += install_folder

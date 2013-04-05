qml_folder.source = ../../Tepee3DEngine/plugins_qml
qml_folder.target = ./

 TEMPLATE        = lib
 CONFIG         += qt plugin
 QT             += quick
 QT             += gui


HEADERS += \
    TwitterPlugin.h

SOURCES += \
    TwitterPlugin.cpp

#include development files
include (../../Tepee3DEngine/DeveloperAPIFiles/DevelopmentFiles.pri)

 TARGET          = TwitterPlugin                  #NAME OF THE PLUGIN LIBRAY
 DESTDIR         = ../../Tepee3DEngine/libraries/widget_libraries             #WHERE TO PUT THE LIBRARY
 DESTDIRQML      = qml_folder

# Copies the given files to the destination directory
defineTest(copyToDestDir) {
    files = $$1
    unix {
        QMAKE_POST_LINK  += rm -fr $$qml_folder.source/$$TARGET $$escape_expand(\\n\\t)
        QMAKE_POST_LINK  += mkdir $$qml_folder.source/$$TARGET $$escape_expand(\\n\\t)
    }
    win32 {
        DDIR = ../plugins_qml/$${TARGET}
        DESTDIR_WIN = $${DDIR}
        DESTDIR_WIN ~= s,/,\\,g
       QMAKE_POST_LINK +=$$quote(cmd /c del /s /f  /q  $${DESTDIR_WIN}$$escape_expand(\n\t))
     #   QMAKE_POST_LINK +=$$quote(cmd /c mkdir /y $${DDIR}escape_expand(\n\t))
    }
    for(FILE, files) {
         DDIR = $$qml_folder.source/$$TARGET/
        # Replace slashes in paths with backslashes for Windows
        win32{
        DDIR = $$qml_folder.source/$${TARGET}
        DESTDIR_WIN = $${DDIR}
        DESTDIR_WIN ~= s,/,\\,g
        PWD_WIN = $${PWD}
        PWD_WIN ~= s,/,\\,g
        for(FILE, OTHER_FILES){
            QMAKE_POST_LINK += $$quote(cmd /c copy /y $${PWD_WIN}\\$${FILE} $${DESTDIR_WIN}$$escape_expand(\\n\\t))
    }
}

        unix:QMAKE_POST_LINK += $$QMAKE_COPY $$quote($$FILE) $$quote($$DDIR) $$escape_expand(\\n\\t)
        win32:QMAKE_POST_LINK +=$$quote(cmd /c copy /y $${FILE} $${DDIR}$$escape_expand(\n\t))

    }
    message($$QMAKE_POST_LINK)
    export(QMAKE_POST_LINK)
}


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/qttweetlib/release/ -lqtweetlib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/qttweetlib/debug/ -lqtweetlib
else:unix: LIBS += -L$$PWD/qttweetlib/ -lqtweetlib

INCLUDEPATH += $$PWD/qttweetlib
DEPENDPATH += $$PWD/qttweetlib
LIBS += -L$$PWD/qttweetlib -lqtweetlib

OTHER_FILES += \
    Menu.qml \
    TwitterPlugin.qml \
    qttweetlib/libqtweetlib.so.1.0.0 \
    qttweetlib/libqtweetlib.so.1.0 \
    qttweetlib/libqtweetlib.so.1 \
    qttweetlib/libqtweetlib.so

# deploy qml files to correct dir
copyToDestDir($$OTHER_FILES)

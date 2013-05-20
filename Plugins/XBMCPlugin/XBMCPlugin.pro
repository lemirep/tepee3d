qml_folder.source = ../../Tepee3DEngine/plugins_qml
qml_folder.target = ./

  TEMPLATE        = lib
  CONFIG         += qt plugin
  QT             += quick

 #include development files
    include (../../Tepee3DEngine/DeveloperAPIFiles/DevelopmentFiles.pri)

 TARGET          = XBMCPlugin
 DESTDIR         = ../../Tepee3DEngine/libraries/widget_libraries
 DESTDIRQML      = qml_folder
# Copies the given files to the destination directory
defineTest(copyToDestDir) {
    files = $$1
    unix {
        QMAKE_POST_LINK  += rm -fr PATH_TO_SAVE_YOUR_FILE/$$TARGET $$escape_expand(\\n\\t)
        QMAKE_POST_LINK  += mkdir PATH_TO_SAVE_YOUR_FILE/$$TARGET $$escape_expand(\\n\\t)
    }
    win32 {
        DDIR = PATH_TO_SAVE_YOUR_FILE/$${TARGET}
        DESTDIR_WIN = $${DDIR}
        DESTDIR_WIN ~= s,/,\\,g
       QMAKE_POST_LINK +=$$quote(cmd /c del /s /f  /q  $${DESTDIR_WIN}$$escape_expand(\n\t))
     #   QMAKE_POST_LINK +=$$quote(cmd /c mkdir /y $${DDIR}escape_expand(\n\t))
    }
    for(FILE, files) {
         DDIR = PATH_TO_SAVE_YOUR_FILE/$$TARGET/
        # Replace slashes in paths with backslashes for Windows
        win32{
        DDIR = PATH_TO_SAVE_YOUR_FILE/$${TARGET}
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


# deploy qml files to correct dir
copyToDestDir($$OTHER_FILES)

HEADERS += \
   XBMCPlugin.h \
    AudioLibrary.h \
    VideoLibrary.h \
    PlayerManager.h \
    IWebRequestDispatcher.h

SOURCES += \
    XBMCPlugin.cpp \
    AudioLibrary.cpp \
    VideoLibrary.cpp \
    PlayerManager.cpp

OTHER_FILES += \
    XBMCPlugin.qml \
    Menu.qml

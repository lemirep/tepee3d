qml_folder.source = PATH_WHERE_YOU_SAVE_YOUR_PLUGINS_QML
qml_folder.target = ./

  TEMPLATE        = lib
  CONFIG         += qt plugin
  QT             += quick
  QT             += gui

 #include development files
    include (../DeveloperAPIFiles/DevelopmentFiles.pri)

 TARGET          = DummyProject
 DESTDIR         = WHERE_TO_PUT_THE LIBRARY
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
    DummyProject.h

SOURCES += \
    DummyProject.cpp

OTHER_FILES += \
    DummyProject.qml \
    Menu.qml

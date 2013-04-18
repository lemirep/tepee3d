qml_folder.source = ../../Tepee3DEngine/plugins_qml
qml_folder.target = ./

  TEMPLATE        = lib
  CONFIG         += qt plugin
  QT             += quick

 #include development files
    include (../../Tepee3DEngine/DeveloperAPIFiles/DevelopmentFiles.pri)

 TARGET          = SeriesPlugin
 DESTDIR         = ../../Tepee3DEngine/libraries/widget_libraries
 DESTDIRQML      = qml_folder
# Copies the given files to the destination directory
defineTest(copyToDestDir) {
    files = $$1
    unix {
        QMAKE_POST_LINK  += rm -fr $$qml_folder.source/$$TARGET $$escape_expand(\\n\\t)
        QMAKE_POST_LINK  += mkdir -p $$qml_folder.source/$$TARGET $$escape_expand(\\n\\t)
    }
    win32 {
        DDIR = $$qml_folder.source/$${TARGET}
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

HEADERS += \
    SeriesPlugin.h \
    SerieSubListedItem.h \
    SeasonSubListedItem.h \
    EpisodeListItem.h

SOURCES += \
    SeriesPlugin.cpp \
    SerieSubListedItem.cpp \
    SeasonSubListedItem.cpp \
    EpisodeListItem.cpp

OTHER_FILES += \
    SeriesPlugin.qml \
    Menu.qml \
    SeriesListViewDelegate.qml \
    qmldir \
    SeasonListViewDelegate.qml \
    EpisodeListViewDelegate.qml \
    SeriesSearchListViewDelegate.qml \
    DetailedEpisodeView.qml \
    SerieBackground.qml \
    SeriesDetailedView.qml \
    SeriePathView.qml \
    SeasonPathView.qml \
    EpisodePathView.qml \
    SearchSerie.qml \
    SickBeardConfig.qml \
    sickbeard_logo.png \
    dvdbox.png \
    sickbeard_search.png \
    check_all.png \
    halo.png

# deploy qml files to correct dir
copyToDestDir($$OTHER_FILES)

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


defineTest(copyToDestDir) {
    files = $$1
    unix {
        QMAKE_POST_LINK  += rm -fr $$qml_folder.source/$$TARGET $$escape_expand(\\n\\t)
        QMAKE_POST_LINK  += mkdir $$qml_folder.source/$$TARGET $$escape_expand(\\n\\t)
    }
    win32 {
        DDIR = ..\..\Tepee3DEngine\plugins_qml\\$$TARGET
        DESTDIR_WIN = $${DDIR}
        DESTDIR_WIN ~= s,/,\\,g
        QMAKE_POST_LINK +=$$quote(cmd /c  if not exist $${DDIR}\NUL\\$$escape_expand(\n\t) mkdir  $${DDIR}$$escape_expand(\n\t))
    }
    for(FILE, files) {
        DDIR = $$qml_folder.source/$$TARGET/

        win32{
        DDIR =  ..\..\Tepee3DEngine\plugins_qml\\$$TARGET
        FILE ~= s,/,\\,g
        QMAKE_POST_LINK +=$$quote(cmd /c copy /y $${FILE} $${DDIR}$$escape_expand(\n\t))
        }

        unix:QMAKE_POST_LINK += $$QMAKE_COPY $$quote($$FILE) $$quote($$DDIR) $$escape_expand(\\n\\t)
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
    qmldir \
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
    planning.png \
    halo.png \
    shadow_separator_h.png \
    SeriesPathViewDelegate.qml \
    EpisodePathViewDelegate.qml \
    SeasonPathViewDelegate.qml \
    SerieListView.qml \
    ShowPlanningView.qml \
    SeriePathViewContainer.qml \
    SeasonEpisodePathViewContainer.qml

# deploy qml files to correct dir
copyToDestDir($$OTHER_FILES)

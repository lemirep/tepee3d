
  TEMPLATE        = lib
  CONFIG         += qt plugin
  QT             += quick

 #include development files
    include (../../Tepee3DEngine/DeveloperAPIFiles/DevelopmentFiles.pri)

 TARGET          = SeriesPlugin
 DESTDIR         = ../../Tepee3DEngine/libraries/widget_libraries
 DESTDIRQML      = qml_folder


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
qml_folder.files = $$OTHER_FILES
qml_folder.path = ../../Tepee3DEngine/plugins_qml/SeriesPlugin

DEPLOYMENT += qml_folder
INSTALLS += qml_folder

  TEMPLATE        = lib
  CONFIG         += qt plugin
  QT             += quick

 #include development files
    include (../../Tepee3DEngine/DeveloperAPIFiles/DevelopmentFiles.pri)

 TARGET          = XBMCPlugin
 DESTDIR         = ../../Tepee3DEngine/libraries/widget_libraries
 DESTDIRQML      = qml_folder

HEADERS += \
   XBMCPlugin.h \
    IWebRequestDispatcher.h \
    PlayableItemModel.h

SOURCES += \
    XBMCPlugin.cpp \
    PlayableItemModel.cpp

OTHER_FILES += \
    XBMCPlugin.qml \
    Menu.qml \
    RemoteItem.qml \
    AudioLibrary.qml \
    Home.qml \
    MoviesLibrary.qml \
    ShowsLibrary.qml \
    music.png \
    movies.png \
    remote.png \
    shows.png \
    empty_cd.png \
    cdbox.png \
    dvdbox.png \
    shadow_separator_h.png \
    JoystickControl.png \
    ArtistLibrary.qml \
    AlbumsLibrary.qml \
    SongsLibrary.qml \
    LibraryGridViewDelegate.qml \
    MoviesGridView.qml \
    MovieDetailView.qml \
    player_play.png \
    player_pause.png \
    player_stop.png \
    player_forward.png \
    player_backward.png \
    player_fforward.png \
    player_fbackward.png \
    AlbumDetailView.qml \
    ArtistAlbumsView.qml

INCLUDEPATH += $$PWD

include (./Audio/Audio.pri)
include (./Video/Video.pri)
include (./Player/Player.pri)
include (./Remote/Remote.pri)

# deploy qml files to correct dir
qml_folder.files = $$OTHER_FILES
qml_folder.path = ../../Tepee3DEngine/plugins_qml/XBMCPlugin

DEPLOYMENT += qml_folder
INSTALLS += qml_folder

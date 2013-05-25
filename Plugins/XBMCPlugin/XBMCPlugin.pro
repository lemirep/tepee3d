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
    IWebRequestDispatcher.h


SOURCES += \
    XBMCPlugin.cpp

OTHER_FILES += \
    XBMCPlugin.qml \
    Menu.qml \
    RemoteItem.qml

include (./Audio/Audio.pri)
include (./Video/Video.pri)
include (./Player/Player.pri)
include (./Remote/Remote.pri)

# deploy qml files to correct dir
qml_folder.files = $$OTHER_FILES
qml_folder.path = ../../Tepee3DEngine/plugins_qml/XBMCPlugin

DEPLOYMENT += qml_folder
INSTALLS += qml_folder

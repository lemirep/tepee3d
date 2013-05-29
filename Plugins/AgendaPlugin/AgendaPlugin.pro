

  TEMPLATE        = lib
  CONFIG         += qt plugin
  QT             += quick

include (../../Tepee3DEngine/DeveloperAPIFiles/DevelopmentFiles.pri)

 TARGET          = AgendaPlugin
 DESTDIR         = ../../Tepee3DEngine/libraries/widget_libraries
 DESTDIRQML      = qml_folder


HEADERS += \
    agendaplugin.h

SOURCES += \
    agendaplugin.cpp

OTHER_FILES += \
    AgendaPlugin.qml \
    Menu.qml \
    AgendaCalendar.qml \
    AgendaCalendarDayRect.qml

# deploy qml files to correct dir
qml_folder.files = $$OTHER_FILES
qml_folder.path = ../../Tepee3DEngine/plugins_qml/AgendaPlugin

DEPLOYMENT += qml_folder
INSTALLS += qml_folder

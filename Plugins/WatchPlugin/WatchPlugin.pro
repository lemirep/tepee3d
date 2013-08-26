  TEMPLATE        = lib
  CONFIG         += qt plugin
  QT             += quick
  QT             += widgets

 #include development files
    include (../../Tepee3DEngine/DeveloperAPIFiles/DevelopmentFiles.pri)

 TARGET          = watch_plugin
 DESTDIR         = ../../Tepee3DEngine/libraries/widget_libraries
 DESTDIRQML      = qml_folder

HEADERS += \
    WatchPlugin.h \
    WatchPlugin.h \
    ClockListItem.h

SOURCES += \
    WatchPlugin.cpp \
    ClockListItem.cpp


OTHER_FILES += \
    WatchPlugin.qml \
    Menu.qml \
    qmldir \
    WatchPlugin.qml \
    Menu.qml \
    qmldir \
    AlarmClock-2.dae \
    enhanced_led_board-7.ttf \
    ClockDelegate.qml \
    Clock.qml \
    second.png \
    minute.png \
    hour.png \
    clock-night.png \
    clock.png \
    center.png \
    background.png \
    plus.png \
    AddBox.qml \
    edit.png \
    delegate.png \
    EditBox.qml \
    RemoveBox.qml

# deploy qml files to correct dir
qml_folder.files = $$OTHER_FILES
qml_folder.path = ../../Tepee3DEngine/plugins_qml/watch_plugin

DEPLOYMENT += qml_folder
INSTALLS += qml_folder


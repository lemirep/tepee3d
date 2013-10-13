# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH = qml/Tepee3DEngine

QT += qml
QT += quick
QT += multimedia
QT += 3dquick
QT += sql

SOURCES += main.cpp

OBJECTS_DIR = tmp

MOC_DIR = tmp

win32:DESTDIR = ./

# Include Shared Development Files
include(DeveloperAPIFiles/DevelopmentFiles.pri)
## Include QmlViewManagement
#include(View/View.pri)
## Include Room Sources
#include(Room/Room.pri)
## Include Services Sources
#include(Services/Services.pri)
## Include Plugins Sources
#include(Plugins/Plugins.pri)

OTHER_FILES += \
    splashscreen.png \
    qml/TepeeCamera.qml \
    qml/Menus/qmldir \
    qml/Menus/MenuTop.qml \
    qml/Menus/MenuRight.qml \
    qml/Menus/MenuLeft.qml \
    qml/Menus/MenuCenter.qml \
    qml/Menus/MenuBottom.qml \
    qml/qmldir \
    qml/main.qml \
    qml/Rooms/qmldir \
    qml/Rooms/Room.qml \
    qml/Rooms/RoomLoader.qml \
    qml/Rooms/RoomsContainer.qml \
    qml/Rooms/RoomDelegate.qml \
    qml/Rooms/RoomWall.qml \
    qml/Rooms/RoomMenuFaceDelegate.qml \
    qml/Plugins/qmldir \
    qml/Plugins/PluginBase.qml \
    qml/Plugins/RoomPluginDelegate.qml \
    qml/Plugins/PluginLoader.qml \
    qml/Plugins/NewPluginDelegate.qml \
    qml/Notifications/qmldir    \
    qml/Notifications/NotificationManager.qml \
    qml/js/Walls.js \
    qml/js/RoomManagement.js \
    qml/js/NotificationManagement.js \
    qml/js/CameraManagement.js \
    qml/FpsCounter.qml \
    qml/Resources/Pictures/arrow.png \
    qml/Resources/Pictures/delegate.png \
    qml/Resources/Pictures/delegate_selected.png \
    qml/Resources/Pictures/panel_bg2.png \
    qml/Resources/Pictures/spinner.png \
    qml/Resources/Pictures/smoke.png \
    qml/Resources/Pictures/plus.png \
    qml/Resources/Textures/wood.jpg \
    qml/Resources/Textures/wall_indicator_north.png \
    qml/Resources/Textures/wall_indicator_south.png \
    qml/Resources/Textures/wall_indicator_east.png \
    qml/Resources/Textures/wall_indicator_west.png \
    qml/Resources/Textures/wall_indicator_up.png \
    qml/Resources/Textures/wall_indicator_down.png \
    qml/content/Clock.qml \
    qml/content/QuitButton.qml \
    qml/second.png \
    qml/quit.png \
    qml/minute.png \
    qml/hour.png \
    qml/clock-night.png \
    qml/clock.png \
    qml/center.png \
    qml/content/second.png \
    qml/content/quit.png \
    qml/content/minute.png \
    qml/content/hour.png \
    qml/content/clock-night.png \
    qml/content/clock.png \
    qml/content/center.png \
    qml/content/background.png \
    qml/Rooms/AddNewRoomDialog.qml \
    qml/Resources/Pictures/home_buttom.png \
    qml/Resources/Pictures/refresh.png \
    qml/Menus/SkyboxPicker.qml

qnx {
    OTHER_FILES += bar-descriptor.xml
}


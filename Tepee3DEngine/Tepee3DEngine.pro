# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH = qml/Tepee3DEngine

QT += qml
QT += quick
QT += multimedia
QT += widgets
QT += 3dquick
QT += sql
QT += testlib

SOURCES += main.cpp

win32:DESTDIR = ./

# Include Shared Development Files
include(../DeveloperAPIFiles/DevelopmentFiles.pri)
# Include QmlViewManagement
include(View/View.pri)
# Include Room Sources
include(Room/Room.pri)
# Include Services Sources
include(Services/Services.pri)
# Include Plugins Sources
include(Plugins/Plugins.pri)

# Please do not modify the following two lines. Required for deployment.
#include(qmlapplicationviewer/qmlapplicationviewer.pri)
#qtcAddDeployment()

OTHER_FILES += \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/manifest.aegis \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog \
    splashscreen.png \
    icon.png \
    bar-descriptor.xml \
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
    qml/Plugins/RoomPluginDelegate.qml \
    qml/Plugins/PluginLoader.qml \
    qml/Plugins/NewPluginDelegate.qml \
    qml/Notifications/qmldir    \
    qml/Notifications/NotificationManager.qml \
    qml/js/Walls.js \
    qml/js/RoomManagement.js \
    qml/js/NotificationManagement.js \
    qml/FpsCounter.qml \
    qml/Resources/Pictures/arrow.png \
    qml/Resources/Pictures/delegate.png \
    qml/Resources/Pictures/delegate_selected.png \
    qml/Resources/Pictures/panel_bg2.png \
    qml/Resources/Pictures/spinner.png \
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
    qml/Resources/Pictures/refresh.png

qnx {
    QMAKE_LFLAGS += '-Wl,-rpath,\'./app/native/lib\''

    PACKAGE_ARGS = \
        $${PWD}/bar-descriptor.xml $$TARGET \
        -e $${PWD}/icon.png res/icon.png \
        -e $$[QT_INSTALL_LIBS]/libQtCore.so.5 lib/libQtCore.so.5 \
        -e $$[QT_INSTALL_LIBS]/libQtGui.so.5 lib/libQtGui.so.5 \
        -e $$[QT_INSTALL_LIBS]/libQtOpenGL.so.5 lib/libQtOpenGL.so.5 \
        -e $$[QT_INSTALL_LIBS]/libQtNetwork.so.5 lib/libQtNetwork.so.5 \
        -e $$[QT_INSTALL_LIBS]/libQtWidgets.so.5 lib/libQtWidgets.so.5 \
        -e $$[QT_INSTALL_LIBS]/libQtQuick.so.5 lib/libQtQuick.so.5 \
        -e $$[QT_INSTALL_LIBS]/libQtQml.so.5 lib/libQtQml.so.5 \
        -e $$[QT_INSTALL_LIBS]/libQtSql.so.5 lib/libQtSql.so.5 \
        -e $$[QT_INSTALL_LIBS]/libQt3DQuick.so.5 lib/libQt3DQuick.so.5  \
        -e $$[QT_INSTALL_LIBS]/libQt3D.so.5 lib/libQt3D.so.5   \
        -e $$[QT_INSTALL_LIBS]/libQtV8.so.5 lib/libQtV8.so.5 \
        -e $$[QT_INSTALL_LIBS]/libQtXmlPatterns.so.5 lib/libQtXmlPatterns.so.5 \
        -e $$[QT_INSTALL_PLUGINS]/platforms/libqnx.so plugins/platforms/libqnx.so \
        -e qml qml \
        -e $$[QT_INSTALL_IMPORTS]/ imports/

    package.target = $${TARGET}.bar
    package.depends = $$TARGET
    package.commands = blackberry-nativepackager \
        -package $${TARGET}.bar \
        -devMode -debugToken $$(DEBUG_TOKEN) \
        $${PACKAGE_ARGS}

    QMAKE_EXTRA_TARGETS += package

    OTHER_FILES += qnx/bar-descriptor.xml
}



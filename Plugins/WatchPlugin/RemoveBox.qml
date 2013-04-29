import QtQuick 2.0

Rectangle
{
    height : parent.height / 8
    width:  parent.width / 8
    anchors.verticalCenter: parent.verticalCenter
    anchors.horizontalCenter: parent.horizontalCenter
    scale : remove_ma.pressed ? 0.9 : 1.0
    Text
    {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        text:"Remove"
    }
    MouseArea{
        id : remove_ma
        anchors.fill: parent
        onClicked:
        {
            WatchPlugin.deleteClockDB(WatchPlugin.getCurrentId());
            WatchPlugin.reInitModel();
            WatchPlugin.pluginState = "clocks_view"
        }
    }
}

import QtQuick 2.1

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
        text:"Remove " + watch_plugin.currentItemChangedCity
    }
    MouseArea{
        id : remove_ma
        anchors.fill: parent
        onClicked:
        {
            watch_plugin.deleteClockDB(watch_plugin.getCurrentId());
            watch_plugin.reInitModel();
            watch_plugin.pluginState = "clocks_view"
        }
    }
}

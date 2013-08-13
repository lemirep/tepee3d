import QtQuick 2.1

// MUST CONTAIN ONLY QtQuick 2 elements, no 3D

Item
{
    anchors.fill: parent

    Rectangle
    {
        color : "transparent"
        anchors.fill: parent
        Text {
            //text : "Menu Setting For plugin" + apc.getPluginName()
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

}

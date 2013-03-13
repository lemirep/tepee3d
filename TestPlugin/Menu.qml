import QtQuick 2.0

// MUST CONTAIN ONLY QtQuick 2 elements, no 3D

Item
{
    anchors.fill: parent

    Rectangle
    {
        color : "transparent"
        anchors.fill: parent
        Text {
<<<<<<< HEAD
            //text : "Menu Setting For plugin" + apc.getPluginName()
=======
            text : "Menu Setting For plugin" + TestPlugin.getPluginName()
>>>>>>> 5dc5c7129beed1d4967ff969121b46f6dc8472ee
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

}

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
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

}

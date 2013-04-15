import QtQuick 2.0

Rectangle {
    id: c
    height : parent.height
    width: parent.width /2
    color : "blue"
    radius: 0
    anchors {
        horizontalCenter: parent.horizontalCenter;
        verticalCenter: parent.verticalCenter;
    }
    Text
    {
        id : cityName
        text : "City : "
        anchors.top : parent.top
        anchors.topMargin: 20
    }
    TextInput
    {
        id : cityNameInpout
        width:  parent.width / 2
        height:  parent.height / 10
        anchors.left: cityName.right
    }
    Text
    {
        id : cityUtc
        text : "UTC : "
        anchors.top : cityName.top
        anchors.topMargin: 20
    }
    TextInput
    {
        id : cityUtcInpout
        width:  parent.width / 2
        height:  parent.height / 10
        anchors.left: cityUtc.right
    }
}

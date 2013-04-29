import QtQuick 2.0

Item {
    id: c
    height : parent.height
    width: parent.width /2
    opacity : 1
    anchors {
        horizontalCenter: parent.horizontalCenter;
        verticalCenter: parent.verticalCenter;
    }
    Text
    {
        id : cityName
        text : "City : "
        opacity : 1
        font.pointSize: 16
        color : "white"
        anchors.top : parent.top
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: parent.width / 4
    }
    BorderImage {
        anchors.verticalCenter: cityName.verticalCenter
        width: parent.width / 3
        height : parent.height / 8
        anchors.left: cityName.right
        opacity : 1
        source :  "./delegate.png"
        TextInput
        {
            id : cityNameInpout
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 30
            width:  parent.width
            color: "white"; selectionColor: "blue"
            font.pixelSize: 16; font.bold: true
            maximumLength: 16
            focus : true
            text : "Your city"
        }
    }

    Text
    {
        id : cityUtc
        text : "UTC : "
        color : "white"
        font.pointSize: 16
        anchors.top : cityName.bottom
        anchors.topMargin: parent.height / 4
        anchors.left: parent.left
        anchors.leftMargin: parent.width / 4
    }
   BorderImage
    {
        anchors.verticalCenter: cityUtc.verticalCenter
        width: parent.width / 3
        height : parent.height / 8
        anchors.left: cityUtc.right
        opacity : 1
        source :  "./delegate.png"
        TextInput
        {
            id : cityUtcInpout
            width:  parent.width
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 30
            color: "white"; selectionColor: "blue"
            font.pixelSize: 16; font.bold: true
            maximumLength: 2
            focus : true
            text : "9"
        }
    }
    Rectangle
    {
        height : parent.height / 8
        width:  parent.width / 4
        anchors.top : cityUtc.bottom
        anchors.topMargin: parent.height / 4
        anchors.horizontalCenter: parent.horizontalCenter
        scale : add_ma.pressed ? 0.9 : 1.0
        Text
        {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            text:"Add"
        }
        MouseArea{
            id : add_ma
            anchors.fill: parent
            onClicked:
            {
                menuBottomMain.isShown = false
                WatchPlugin.addClockToDB(cityNameInpout.text,cityUtcInpout.text);
                WatchPlugin.reInitModel();
                WatchPlugin.pluginState = "clocks_view"
            }
        }
    }
}

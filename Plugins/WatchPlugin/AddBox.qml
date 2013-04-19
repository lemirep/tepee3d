import QtQuick 2.0

Rectangle {
    id: c
    height : parent.height
    width: parent.width /2
    color : "blue"
    radius: 1
    opacity : 0.5
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
        anchors.top : parent.top
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: parent.width / 4
    }
    Rectangle
    {
        anchors.top : parent.top
        anchors.topMargin: 20
        width: parent.width / 3
        height : parent.height / 8
        anchors.left: cityName.right
        opacity : 1
        color : "red"
        border { color: "green" ;width: 2}
        TextInput
        {
            id : cityNameInpout
            anchors.fill: parent
            color: "#151515"; selectionColor: "green"
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
        font.pointSize: 16
        anchors.top : cityName.bottom
        anchors.topMargin: parent.height / 4
        anchors.left: parent.left
        anchors.leftMargin: parent.width / 4
    }
    Rectangle
    {
        anchors.top : cityUtc.top
        //anchors.topMargin: 20
        width: parent.width / 3
        height : parent.height / 8
        anchors.left: cityUtc.right
        opacity : 1
        color : "red"
        border { color: "green" ;width: 2}
        TextInput
        {
            id : cityUtcInpout
            anchors.fill: parent
            color: "#151515"; selectionColor: "green"
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
                view.visible = true;
                addbox.visible = false;
                add_clock_button.visible = true;

                WatchPlugin.addClockToDB(cityNameInpout.text,cityUtcInpout.text);
                WatchPlugin.getClockModel().clear();
                WatchPlugin.reInitModel();
            }
        }
    }
}

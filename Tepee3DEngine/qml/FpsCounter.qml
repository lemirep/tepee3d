import QtQuick 2.1

Item
{
    id : fpscounter
    property int frameCounter : 0
    property int fps : 0

    width : 60
    height : 60

    Image
    {
        width : 60
        height : 60
        id : spinner
        source : "Resources/Pictures/spinner.png"
        NumberAnimation on rotation
        {
            from : 0
            to : 360
            duration : 1000
            loops : Animation.Infinite
        }
        onRotationChanged: frameCounter++;
    }

    Text
    {
        text : fpscounter.fps + " Fps"
        color : "white"
        anchors
        {
            left : spinner.left
            leftMargin : 12
            verticalCenter : spinner.verticalCenter
        }
    }

    Timer
    {
        interval : 2000
        repeat : true
        running : true
        onTriggered:
        {
            fps = frameCounter / 2
            frameCounter = 0
        }
    }

}

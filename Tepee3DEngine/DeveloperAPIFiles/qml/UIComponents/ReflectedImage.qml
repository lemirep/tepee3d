import QtQuick 2.1

Item
{
    property alias fillMode : main_pic.fillMode
    property alias source : main_pic.source
    property alias asynchronous : main_pic.asynchronous
    property alias cache : main_pic.cache
    property real  reflectRatio : 0.5
    property alias reflectOpacity : reflect_pic.opacity

    width : main_pic.width

    Image
    {
        id : main_pic
        height : parent.height
        anchors.top: parent.top
        anchors.left: parent.left
    }

    Rectangle
    {
        anchors.top: main_pic.bottom
        width:  main_pic.width
        height: main_pic.height * reflectRatio
        clip : true
        Image
        {
            id : reflect_pic
            source : main_pic.source
            anchors.top: parent.top
            fillMode : main_pic.fillMode
            width : main_pic.width
            transform: Rotation {
                origin.x: width / 2
                origin.y: height / 2
                axis.x: 1; axis.y: 0; axis.z: 0
                angle: 180
            }
            opacity : 0.9
        }

        gradient: Gradient {
            GradientStop
            {
                position: 1.0
                color: "#FF000000"
            }
            GradientStop
            {
                position: 0.0
                color: "#00000000"
            }
        }
    }
}

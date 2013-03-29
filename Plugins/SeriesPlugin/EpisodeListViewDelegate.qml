import QtQuick 2.0

Item
{
    id : episode_delegate_item

    property int episodeNumber
    property date episodeAiring
    property string episodeTitle
    property string episodeOverview
    property string img_src

    scale : episode_delegate_ma.pressed ? 0.9 : 1

    Behavior on scale {SmoothedAnimation {velocity : 10}}

//    Rectangle
//    {
//        anchors.fill: parent
//        border
//        {
//            width : 1
//            color : "white"
//        }
//        color : "transparent"
//    }

    Image
    {
        id : episode_delegate_pic
        fillMode : Image.PreserveAspectFit
        asynchronous : true
        height : parent.height - 10
        anchors
        {
            left : parent.left
            verticalCenter : parent.verticalCenter
            leftMargin : 10
        }
        source : img_src
    }

    Text
    {
        id : episode_delegate_text
        anchors
        {
            left : episode_delegate_pic.right
            right : parent.right
            verticalCenter : parent.verticalCenter
            rightMargin : 10
            leftMargin : 10
        }
        color : "white"
        text : episodeTitle
    }

    MouseArea
    {
        id : episode_delegate_ma
        anchors.fill: parent

        onClicked:
        {
            cube_effect.texture = img_src
            rotate_cube.restart()
        }
    }
}

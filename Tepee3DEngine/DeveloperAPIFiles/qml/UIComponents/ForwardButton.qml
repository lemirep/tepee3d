import QtQuick 2.1

Image
{
    id : forward_button
    signal clicked()
    property bool pressed : forward_button_ma.pressed

    height : 50
    width : 50
    scale : forward_button_ma.pressed ? 0.9 : 1
    source : "../Resources/Pictures/small_arrow.png"
    fillMode: Image.PreserveAspectFit
    rotation : 180
    MouseArea
    {
        id : forward_button_ma
        anchors.fill: parent
        onClicked: {forward_button.clicked()}
    }
}

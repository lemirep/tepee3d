import QtQuick 2.0

Image
{
    id : add_button
    signal clicked()
    height : 50
    width : 50
    scale : add_button_ma.pressed ? 0.9 : 1
    source : "plus.png"
    fillMode: Image.PreserveAspectFit
    MouseArea
    {
        id : add_button_ma
        anchors.fill: parent
        onClicked: {add_button.clicked()}
    }
}
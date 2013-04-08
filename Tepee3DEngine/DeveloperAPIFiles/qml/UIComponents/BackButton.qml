import QtQuick 2.0

Image
{
    id : back_button
    signal clicked()
    height : 50
    width : 50
    scale : back_button_ma.pressed ? 0.9 : 1
    source : "small_arrow.png"
    fillMode: Image.PreserveAspectFit
    MouseArea
    {
        id : back_button_ma
        anchors.fill: parent
        onClicked: {back_button.clicked()}
    }
}

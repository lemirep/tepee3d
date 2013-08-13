import QtQuick 2.1

Image
{
    id : back_button
    signal clicked()
    property bool pressed : back_button_ma.pressed

    height : 50
    width : 50
    scale : back_button_ma.pressed ? 0.9 : 1
    source : "back_curved_arrow.png"
    fillMode: Image.PreserveAspectFit
    MouseArea
    {
        id : back_button_ma
        anchors.fill: parent
        onClicked: {back_button.clicked()}
    }
}

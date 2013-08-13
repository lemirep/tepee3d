import QtQuick 2.1

Image
{
    id : arrow_button
    signal clicked()
    property bool reversed : false
    height : 64
    width : 64
    scale : arrow_button_ma.pressed ? 0.9 : 1
    source : "simple_arrow.png"
    fillMode: Image.PreserveAspectFit
    rotation: reversed ? 180 : 0
    MouseArea
    {
        id : arrow_button_ma
        anchors.fill: parent
        onClicked: {arrow_button.clicked()}
    }
}


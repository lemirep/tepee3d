import QtQuick 2.0

Image
{
    id : refresh_button
    signal clicked()
    property bool pressed : refresh_button_ma.pressed

    height : 50
    width : 50
    scale : refresh_button_ma.pressed ? 0.9 : 1
    source : "refresh.png"
    fillMode: Image.PreserveAspectFit
    MouseArea
    {
        id : refresh_button_ma
        anchors.fill: parent
        onClicked: {refresh_button.clicked()}
    }
}

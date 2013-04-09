import QtQuick 2.0

Image
{
    id : settings_button
    signal clicked()
    height : 50
    width : 50
    scale : settings_button_ma.pressed ? 0.9 : 1
    source : "spanner.png"
    fillMode: Image.PreserveAspectFit
    MouseArea
    {
        id : settings_button_ma
        anchors.fill: parent
        onClicked: {settings_button.clicked()}
    }
}

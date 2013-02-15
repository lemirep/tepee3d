import QtQuick 2.0

Item
{
    anchors.fill: parent

    TextInputComponent
    {
        anchors.centerIn: parent
        width : 250
    }
    TextInputComponent
    {
        anchors.bottom : parent.bottom
        width : 250
    }
}

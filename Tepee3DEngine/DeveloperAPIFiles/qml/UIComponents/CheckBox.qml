import QtQuick 2.0

Rectangle
{
    property bool checked : false
    signal toggle();

    onCheckedChanged:
    {
        toggle();
    }

    width : 50
    height : width
    color : "transparent"
    border
    {
        width : 1
        color : "grey"
    }
    radius : width / 2
    smooth : true

    Rectangle
    {
        width : parent.width - 8
        height : width
        radius : width / 2
        smooth : true

        opacity : checked ? 1 : 0
        Behavior on opacity {NumberAnimation {duration : 500}}

        anchors.centerIn: parent

        gradient : Gradient {
            GradientStop
            {
                position : 0.0
                color : "#00ccff"
            }
            GradientStop
            {
                position : 1.0
                color : "#0066cc"
            }
        }
    }

    MouseArea
    {
        anchors.fill: parent
        onClicked : checked = !checked
    }
}

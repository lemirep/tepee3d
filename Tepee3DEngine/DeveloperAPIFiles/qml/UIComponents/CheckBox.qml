import QtQuick 2.1

/*!
\qmlType SettingsButton
\inqmlmodule DeveloperAPIFiles.qml.UIComponents 1.0
\inherits Rectangle
\brief Provides a checkbox.

By the default, the height and the width are set to 50.

\qml
import QtQuick 2.1
import DeveloperAPIFiles.qml.UIComponents 1.0 as UIComponents

UIComponents.CheckBox
{
    onToggle :
    {
        console.log("Settings button was pressed");
    }
}
\endqml

*/

Rectangle
{
    property bool checked : false

    /*!
        This signal is emitted when the user clicks the checkbox. The corresponding handler is
        \c onToggle.
    */
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

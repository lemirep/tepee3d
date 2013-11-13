import QtQuick 2.1

/*!
\qmlType CloseButton
\inqmlmodule DeveloperAPIFiles.qml.UIComponents 1.0
\inherits Image
\brief Provides a close sign button.

By the default, the height and the width are set to 50.

\qml
import QtQuick 2.1
import DeveloperAPIFiles.qml.UIComponents 1.0 as UIComponents

UIComponents.CloseButton
{
    onClicked :
    {
        console.log("Close button was pressed");
    }
}
\endqml

*/

Image
{
    id : close_button

    /*!
        This signal is emitted when the user clicks the button. A click is defined
        as a press followed by a release. The corresponding handler is
        \c onClicked.
    */
    signal clicked()
    property bool pressed : close_button_ma.pressed

    height : 50
    width : 50
    scale : close_button_ma.pressed ? 0.9 : 1
    source : "../Resources/Pictures/red_cross.png"
    fillMode: Image.PreserveAspectFit
    MouseArea
    {
        id : close_button_ma
        anchors.fill: parent
        onClicked: {close_button.clicked()}
    }
}

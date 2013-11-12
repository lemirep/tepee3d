import QtQuick 2.1

/*
\qmlType BackButton
\inqmlmodule DeveloperAPIFiles.qml.UIComponents 1.0
\inherits Image
\brief Provides a back button.

By the default, the height and the width are set to 50.

\qml
import QtQuick 2.1
import DeveloperAPIFiles.qml.UIComponents 1.0 as UIComponents

UIComponents.BackButton
{
    onClicked :
    {
        console.log("Add button was pressed");
    }
}
\endqml

*/

Image
{
    id : back_button

    /*
        This signal is emitted when the user clicks the button. A click is defined
        as a press followed by a release. The corresponding handler is
        \c onClicked.
    */
    signal clicked()
    property bool pressed : back_button_ma.pressed

    height : 50
    width : 50
    scale : back_button_ma.pressed ? 0.9 : 1
    source : "../Resources/Pictures/back_curved_arrow.png"
    fillMode: Image.PreserveAspectFit
    MouseArea
    {
        id : back_button_ma
        anchors.fill: parent
        onClicked: {back_button.clicked()}
    }
}

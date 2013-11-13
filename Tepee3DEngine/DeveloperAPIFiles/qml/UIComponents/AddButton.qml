import QtQuick 2.1

/*!
\qmlType AddButton
\inqmlmodule DeveloperAPIFiles.qml.UIComponents 1.0
\inherits Image
\brief Provides a plus sign button.

By the default, the height and the width are set to 50.

\qml
import QtQuick 2.1
import DeveloperAPIFiles.qml.UIComponents 1.0 as UIComponents

UIComponents.AddButton
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
    id : add_button

    /*
        This signal is emitted when the user clicks the button. A click is defined
        as a press followed by a release. The corresponding handler is
        \c onClicked.
    */
    signal clicked()
    property bool pressed : add_button_ma.pressed
    height : 50
    width : 50
    scale : add_button_ma.pressed ? 0.9 : 1
    source : "../Resources/Pictures/plus.png"
    fillMode: Image.PreserveAspectFit
    MouseArea
    {
        id : add_button_ma
        anchors.fill: parent
        onClicked: {add_button.clicked()}
    }
}

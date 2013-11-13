import QtQuick 2.1

/*!
\qmlType RefreshButton
\inqmlmodule DeveloperAPIFiles.qml.UIComponents 1.0
\inherits Image
\brief Provides a refresh button.

By the default, the height and the width are set to 50.

\qml
import QtQuick 2.1
import DeveloperAPIFiles.qml.UIComponents 1.0 as UIComponents

UIComponents.RefreshButton
{
    onClicked :
    {
        console.log("Refresh button was pressed");
    }
}
\endqml

*/

Image
{
    id : refresh_button

    /*!
        This signal is emitted when the user clicks the button. A click is defined
        as a press followed by a release. The corresponding handler is
        \c onClicked.
    */
    signal clicked()
    property bool pressed : refresh_button_ma.pressed

    height : 50
    width : 50
    scale : refresh_button_ma.pressed ? 0.9 : 1
    source : "../Resources/Pictures/refresh.png"
    fillMode: Image.PreserveAspectFit
    MouseArea
    {
        id : refresh_button_ma
        anchors.fill: parent
        onClicked: {refresh_button.clicked()}
    }
}

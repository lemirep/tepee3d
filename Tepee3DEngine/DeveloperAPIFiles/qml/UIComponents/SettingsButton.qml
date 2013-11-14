import QtQuick 2.1


/*!
\qmltype SettingsButton
\inqmlmodule DeveloperAPIFiles.qml.UIComponents 1.0
\inherits QtQuick::Image
\brief Provides a settings button.

By the default, the height and the width are set to 50.

\qml
import QtQuick 2.1
import DeveloperAPIFiles.qml.UIComponents 1.0 as UIComponents

UIComponents.SettingsButton
{
    onClicked :
    {
        console.log("Settings button was pressed");
    }
}
\endqml

*/

Image
{
    id : settings_button

    /*!
        This signal is emitted when the user clicks the button. A click is defined
        as a press followed by a release. The corresponding handler is
        \c onClicked.
    */
    signal clicked()
    property bool pressed : settings_button_ma.pressed

    height : 50
    width : 50
    scale : settings_button_ma.pressed ? 0.9 : 1
    source : "../Resources/Pictures/spanner.png"
    fillMode: Image.PreserveAspectFit
    MouseArea
    {
        id : settings_button_ma
        anchors.fill: parent
        onClicked: {settings_button.clicked()}
    }
}

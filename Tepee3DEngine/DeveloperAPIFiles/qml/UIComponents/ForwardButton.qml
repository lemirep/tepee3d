import QtQuick 2.1

/*!
\qmltype ForwardButton
\inqmlmodule DeveloperAPIFiles.qml.UIComponents 1.0
\inherits QtQuick::Image
\brief Provides a forward button.

By the default, the height and the width are set to 50.

\qml
import QtQuick 2.1
import DeveloperAPIFiles.qml.UIComponents 1.0 as UIComponents

UIComponents.ForwardButton
{
    onClicked :
    {
        console.log("Forward button was pressed");
    }
}
\endqml

*/

Image
{
    id : forward_button

    /*!
        This signal is emitted when the user clicks the button. A click is defined
        as a press followed by a release. The corresponding handler is
        \c onClicked.
    */
    signal clicked()
    property bool pressed : forward_button_ma.pressed

    height : 50
    width : 50
    scale : forward_button_ma.pressed ? 0.9 : 1
    source : "../Resources/Pictures/small_arrow.png"
    fillMode: Image.PreserveAspectFit
    rotation : 180
    MouseArea
    {
        id : forward_button_ma
        anchors.fill: parent
        onClicked: {forward_button.clicked()}
    }
}

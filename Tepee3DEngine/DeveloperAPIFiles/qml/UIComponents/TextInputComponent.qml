import QtQuick 2.1

/*
\qmlType TextInputComponent
\inqmlmodule DeveloperAPIFiles.qml.UIComponents 1.0
\inherits Item
\brief Provides a text input.

By the default, the height is set to 28.

\qml
import QtQuick 2.1
import DeveloperAPIFiles.qml.UIComponents 1.0 as UIComponents

UIComponents.TextInputComponent
{
    placeHolder : "Enter text Here"
    onAccepted :
    {
        console.log("You wrote " + text);
    }
}
\endqml

*/

Item
{
    id : textFocusScope

    /*!
    \qmlproperty TextInputComponent::placeHolder
    Holds the text to show when no input is done.
    */
    property alias placeHolder : placeHolderText.text
    /*!
    \qmlproperty TextInputComponent::echoMode
    Sets the type of echo mode :
    \list
    \li TextInput.Normal
    \li TextInput.Password
    \li TextInput.NoEcho
    \li TextInput.PasswordEchoOnEdit
    \endlist
    sa TextInput.echoMode
    */
    property alias echoMode : textInput.echoMode
    /*!
    \qmlproperty TextInputComponent::text
    Contains the current text in the input. (Not including the place holder)
    */
    property alias text : textInput.text
    /*
        This signal is emitted when the validates the input. The corresponding handler is
        \c onAccepted.
    */
    signal accepted()
    height : 28

    BorderImage
    {
        id: border
        source: "../Resources/Pictures/text_input_border.png"
        anchors.fill: parent
        border.left: 5; border.top: 5
        border.right: 5; border.bottom: 5
    }
    BorderImage
    {
        id: border_selected
        source: "../Resources/Pictures/text_input_border_selected.png"
        anchors.fill: parent
        border.left: 5; border.top: 5
        border.right: 5; border.bottom: 5
        opacity : textInput.activeFocus == true ? 1 : 0
        Behavior on opacity {SmoothedAnimation {duration : -1; velocity : 5}}
    }

    Text
    {
        id : placeHolderText
        anchors.fill: parent; anchors.leftMargin: 8
        verticalAlignment: Text.AlignVCenter
        text: "Type something..."
        color: "gray"
        font.italic: true
        visible : textInput.text.length == 0
    }

    TextInput
    {
        id : textInput
        clip : true
        anchors
        {
            left : parent.left
            right : parent.right
            leftMargin : 8
            rightMargin : 8
            verticalCenter : parent.verticalCenter
        }
        selectByMouse: true
        onAccepted: {textFocusScope.accepted(); textInput.focus = false}
    }
}

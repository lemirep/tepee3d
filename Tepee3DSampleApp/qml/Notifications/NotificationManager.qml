import QtQuick 2.0


Item
{
    id : notifications_item
    opacity : 0
    property string message;

    width : mainWindow.width / 2
    height : mainWindow.height / 2
    anchors.centerIn: parent

    Behavior on opacity {SmoothedAnimation {velocity : 10; duration : -1}}

    function    sendMessage(message, type)
    {
        // CALL THE GIVEN TYPE OF NOTIFICATION HERE
        console.log("<<<<< NOTIF " + message)
        notifications_item.message = message
        show_notification.start()
    }

    SequentialAnimation
    {
        id : show_notification
        SmoothedAnimation {velocity : 1; duration : -1;target : notifications_item; property : "opacity"; to : 1}
        PauseAnimation { duration: 1500 }
        SmoothedAnimation {velocity : 10; duration : -1;target : notifications_item; property : "opacity"; to : 0}
    }

    BorderImage
    {
        id: background
        source: "../Resources/Pictures/delegate.png"
        anchors.fill: parent
    }

    Text
    {
        anchors.centerIn: background
        text : message
    }

}


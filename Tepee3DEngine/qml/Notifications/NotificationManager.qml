import QtQuick 2.0

Item
{
    id : notifications_item
    property string message;
    property bool   isShown : !(main_notification.opacity == 0);
    anchors.fill: parent

    Behavior on opacity {SmoothedAnimation {velocity : 10; duration : -1}}
    Component.onCompleted: {NotificationManagement.initialize()}

    function    sendMessage(message, type) // TYPE CAN BE ERROR / WARNING / QUICK
    {
        // CALL THE GIVEN TYPE OF NOTIFICATION HERE
        console.log("<<<<< NOTIF " + message)
//        notifications_item.message = message
//        show_notification.start()
        NotificationManagement.addMessage(message);
        if (!isShown)
            showNextMessageInQueue();
    }

    onIsShownChanged: {if (!isShown) showNextMessageInQueue()}

    function    showNextMessageInQueue()
    {
        var msg = null;
        if (NotificationManagement.messages.length > 0)
            msg = NotificationManagement.messages.shift()
        if (msg)
        {
            console.log("Message retrieved");
            notifications_item.message = message
            show_notification.restart()
        }
    }

    // STORE MESSAGES IN A LIST
    // WHILE THERE ARE MESSAGES IN THE LIST SHOW THEM
    // THAT WAY IF MULTIPLE MESSAGES ARE SEND, NONE WILL BE LOST

    // DEFINE ALL MESSAGES TYPE WARNING, ERROR, YES/NO, OK .....

    function    showPopUp(url)    {dialogLoader.source = url; main_notification.opacity = 1}

    SequentialAnimation
    {
        id : show_notification
        SmoothedAnimation {velocity : 1; duration : -1;target : main_notification; property : "opacity"; to : 1}
        PauseAnimation { duration: 1500 }
        SmoothedAnimation {velocity : 10; duration : -1;target : main_notification; property : "opacity"; to : 0}
    }

    Item
    {
        id : main_notification
        width : mainWindow.width / 2
        height : mainWindow.height / 2
        anchors.centerIn: parent
        opacity : 0

        BorderImage
        {
            id: background_main_notification
            source: "../Resources/Pictures/panel_bg2.png"
            anchors.fill: parent
        }

        Text
        {
            anchors.centerIn: background_main_notification
            text : message
        }

        Loader
        {
            anchors.fill: background_main_notification
            id : dialogLoader
        }

        Image
        {
            id : close_main_notification_button
            anchors {right : background_main_notification.right; bottom : background_main_notification.bottom}
            width : 50
            source : "../Resources/Pictures/red_cross.png"
            scale : (close_main_notification_ma.pressed) ? 0.9 : 1
            fillMode: Image.PreserveAspectFit
            MouseArea
            {
                id : close_main_notification_ma
                anchors.fill: parent
                onClicked: {main_notification.opacity = 0}
            }
        }
    }

    Item        // USED TO SIGNAL TWITS, UPDATES ...
    {
        id : quick_notification
        opacity : 0

        BorderImage
        {
            id: background_quick_notification
            source: "../Resources/Pictures/panel_bg2.png"
            anchors.fill: parent
        }
    }
}


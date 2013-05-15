import QtQuick 2.0
import "../js/NotificationManagement.js" as NotificationManagement

Item
{
    id : notifications_item
//    property bool   quickNotifIsShown : quick_notification.isShown;
//    property bool   mainNotifIsShown  : main_notification.isShown;
    anchors.fill: parent

    Behavior on opacity {SmoothedAnimation {velocity : 10; duration : -1}}
    Component.onCompleted: {NotificationManagement.initialize()}

    function    sendMessage(message) // TYPE CAN BE ERROR / WARNING / QUICK
    {
        // MESSAGE IS A JSON OF THE FORM
        //        message ={
        //                    message : "textMessage", // NEEDED
        //                    type : 0,                // NEEDED
        //                    callback :               // OPTIONAL IF QUICK NOTIF
        //                    {
        //                        func : testCal,
        //                        context : this
        //                    }
        //                  }
        // TYPE 0 -> Quick, 1 -> Confirmation (calls callback with true or false as param), 2 ->  Warning (Ok Button), 3 -> Error (Ok Button)

        // CALL CALLBACK TO BE EXECUTED IN THE CONTEXT OF SENDER
        //        message.callback.call(message.sender);
        //        callback.call(sender);


        if (!message || (message.type === null) || !message.message)
            return;

        switch (message.type)
        {
            // MESSAGES ARE SAVED IN CORRESPONDING QUEUE
        case 0: // QUICK NO CALLBACK NEEDED
            if (message.callback && message.callback.func && message.callback.context)
                NotificationManagement.addQuickMessage(message);
            if (!quick_notification.isShown)
                showNextQuickMessageInQueue();
            break;
        case 1: // Confirmation (CALLBACK WITH TRUE FALSE)
            if (message.callback && message.callback.func && message.callback.context)
                NotificationManagement.addMessage(message);
            if (!main_notification.isShown)
                showNextMessageInQueue();
            break;
        case 2: // WARNING (CALLBACK NO PARAMS)
            NotificationManagement.addMessage(message);
            if (!main_notification.isShown)
                showNextMessageInQueue();
            break;
        case 3: // ERROR (CALLBACK NO PARAMS)
            NotificationManagement.addMessage(message);
            if (!main_notification.isShown)
                showNextMessageInQueue();
            break;
        }
    }

    function    showNextMessageInQueue()
    {
        var msg = null;
        if (NotificationManagement.nextMessage())
            msg = NotificationManagement.getNextMessage()
        if (msg)
        {
            console.log("Message retrieved");
            main_notification.isShown = true;
        }
    }

    function    showNextQuickMessageInQueue()
    {
        var msg = null;
        if (NotificationManagement.nextQuickMessage())
            msg = NotificationManagement.getNextQuickMessage()
        if (msg)
        {
            console.log("Message retrieved");
            quick_notification.isShown = true;
        }
    }

    // STORE MESSAGES IN A LIST
    // WHILE THERE ARE MESSAGES IN THE LIST SHOW THEM
    // THAT WAY IF MULTIPLE MESSAGES ARE SEND, NONE WILL BE LOST
    // DEFINE ALL MESSAGES TYPE WARNING, ERROR, YES/NO, OK .....

    Item
    {
        id : main_notification
        property bool isShown : false;
        enabled : isShown
        width : mainWindow.width / 2
        height : mainWindow.height / 2
        anchors.centerIn: parent
        opacity : 0
        Behavior on opacity {SmoothedAnimation {duration : -1; velocity : 5}}

        onIsShownChanged:
        {
            opacity = (isShown) ? 1 : 0;
            if (isShown)
            {
                button_validate.opacity = 0;
                button_cancel.opacity = 0;
                var msg = NotificationManagement.getLastMessage();
                if (msg && msg.type !== null)
                {
                    main_notification_text.text = msg.message;
                    switch (msg.type)
                    {
                    case 1:
                        button_validate.isSingle = false;
                        button_validate.opacity = 1;
                        button_cancel.opacity = 1;
                        break;
                    case 2:
                        button_validate.isSingle = true;
                        button_validate.opacity = 1;
                        break;
                    case 3:
                        button_validate.isSingle = true;
                        button_validate.opacity = 1;
                        break;
                    }
                }
            }
            else
                showNextMessageInQueue();
        }

        BorderImage
        {
            id: background_main_notification
            source: "../Resources/Pictures/panel_bg2.png"
            anchors.fill: parent
        }

        Text
        {
            id : main_notification_text
            anchors.centerIn: background_main_notification
            color : "white"
        }

        Loader
        {
            anchors.fill: background_main_notification
            id : dialogLoader
        }

        // VALIDATE BUTTON OR OK BUTTON
        Image
        {
            id : button_validate
            property bool isSingle;
            height : 50
            source : "../Resources/Pictures/arrow.png"
            scale : (button_validate_ma.pressed) ? 0.9 : 1
            fillMode: Image.PreserveAspectFit

            anchors.bottom : parent.bottom
            onIsSingleChanged:
            {
                if (isSingle)
                    anchors.horizontalCenter = parent.horizontalCenter;
                else
                    anchors.right = parent.horizontalCenter
            }
            MouseArea
            {
                id : button_validate_ma
                anchors.fill: parent
                onClicked :
                {
                    var msg = NotificationManagement.getLastMessage()
                    if (msg)
                        msg.callback.func.call(msg.callback.context, (msg.type === 1) ? true : null);
                    main_notification.isShown = !main_notification.isShown;
                }
            }
        }
        // CANCEL BUTTON
        Image
        {
            id : button_cancel
            width : 50
            source : "../Resources/Pictures/red_cross.png"
            scale : (button_cancel_ma.pressed) ? 0.9 : 1
            fillMode: Image.PreserveAspectFit
            anchors
            {
                left : parent.horizontalCenter
                bottom : parent.bottom
            }
            MouseArea
            {
                id : button_cancel_ma
                anchors.fill: parent
                onClicked :
                {
                    var msg = NotificationManagement.getLastMessage()
                    if (msg)
                        msg.callback.func.call(msg.callback.context, false);
                    main_notification.isShown = !main_notification.isShown;
                }
            }
        }
    }

    Item        // USED TO SIGNAL TWITTS, UPDATES ...
    {
        id : quick_notification
        property bool isShown : false;
        enabled : isShown
        opacity : 0
        Behavior on opacity {SmoothedAnimation {duration : -1; velocity : 5}}

        Timer
        {
            id : hide_quick_notif_timer
            interval : 1500
            repeat : false;
            running : false;
            onTriggered:    {quick_notification.isShown = false;}
        }

        onIsShownChanged :
        {
            opacity = (isShown) ? 1 : 0;
            if (isShown)
            {
                var msg = NotificationManagement.getLastQuickMessage();
                if (msg)
                    quick_notification_text.text = msg.message;
                hide_quick_notif_timer.start();
            }
            else
                showNextQuickMessageInQueue();
        }

        width : mainWindow.width / 4
        height : 100

        anchors
        {
            right : parent.right
            verticalCenter : parent.verticalCenter
        }

        BorderImage
        {
            id: background_quick_notification
            source: "../Resources/Pictures/panel_bg2.png"
            anchors.fill: parent
        }

        Text
        {
            id : quick_notification_text
            anchors.centerIn: background_quick_notification
            color : "white"
        }

        MouseArea
        {
            anchors.fill: parent
            onClicked :
            {
            }
        }
    }
}


import QtQuick 2.1

Item
{
    enabled: isShown
    width  : maxMenuWidth
    height: maxMenuHeight / 20
    // Quit Tepee3d buttom
    BorderImage
    {
        id : quitButtom
        source :  (quitMouse.pressed ) ? "../Resources/Pictures/delegate_selected.png" : "../Resources/Pictures/delegate.png"
        width  : maxMenuWidth / 4
        height: maxMenuHeight / 2
        scale : quitMouse.pressed ? 0.8 : 1.0
        opacity : 0.9
        Text
        {
            anchors
            {
                verticalCenter : parent.verticalCenter
                horizontalCenter : parent.horizontalCenter
            }
            text : "Quit Tepee3D"
            color : "white"
            font.pointSize: mainWindow.largeFontSize
        }
        MouseArea {
            id: quitMouse
            // enabled: false
            anchors.fill: parent
            onClicked :{
                confirmation.opacity = 1;
                quitButtom.opacity = 0;
            }
        }
    }
    // ask confirmation to quit  ; Are you sure ? buttom
    BorderImage
    {
        id : confirmation
        opacity : 0
        width  : maxMenuWidth / 2
        height: maxMenuHeight / 1.5
        anchors.horizontalCenter: parent.horizontalCenter
        Behavior on opacity {SmoothedAnimation {velocity : 1}}
        source :  "../Resources/Pictures/delegate.png"
        Text
        {
            anchors
            {
                top : parent.top
                topMargin : parent.height / 5
                horizontalCenter : parent.horizontalCenter
            }
            text : "Are you sure ?"
            color : "white"
            font.pointSize: mainWindow.largeFontSize
        }
        // No buttom
        BorderImage
        {
            width: parent.width / 3
            height :  parent.height / 3
            source :  "../Resources/Pictures/delegate_selected.png"

            //  color : "steelblue"
            anchors
            {
                bottom : parent.bottom
                bottomMargin : parent.height / 5
                left : parent.left
                leftMargin : parent.width / 10
            }

            Text
            {
                anchors
                {
                    verticalCenter : parent.verticalCenter
                    horizontalCenter : parent.horizontalCenter
                }
                text : "No"
                color : "white"
                font.pointSize: mainWindow.defaultFontSize
            }

            MouseArea {
                anchors.fill: parent
                onClicked :{
                    confirmation.opacity = 0;
                    quitButtom.opacity = 1;
                }
            }
        }
        //Yes buttom
        BorderImage {
            width: parent.width / 3
            height :  parent.height / 3
            source :  "../Resources/Pictures/delegate_selected.png"
            anchors
            {
                bottom : parent.bottom
                bottomMargin : parent.height / 5
                right : parent.right
                rightMargin : parent.width / 10
            }
            Text
            {
                anchors
                {
                    verticalCenter : parent.verticalCenter
                    horizontalCenter : parent.horizontalCenter
                }
                text : "Yes"
                color : "white"
                font.pointSize: mainWindow.defaultFontSize
            }          
            MouseArea {
                anchors.fill: parent
                onClicked :{
                    Qt.quit();
                }
            }

        }
    }

}


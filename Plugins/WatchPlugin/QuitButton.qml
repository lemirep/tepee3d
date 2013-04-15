import QtQuick 2.0

Item
{
    enabled: isShown
    width  : maxMenuWidth
    height: maxMenuHeight / 20
    // Quit Tepee3d buttom
    Rectangle
    {
        id : quitButtom
        color : "blue"
        width  : maxMenuWidth / 4
        height: maxMenuHeight / 2
        radius : 5
        scale : quitMouse.pressed ? 0.8 : 1.0
        opacity : 0.9
       // anchors.horizontalCenter: parent.horizontalCenter
        border
        {
            width: 2;
            color: "white"
        }
        Text
        {
            anchors
            {
                verticalCenter : parent.verticalCenter
                horizontalCenter : parent.horizontalCenter
            }
            text : "Quit Tepee3D"
            color : "white"
            font.pointSize: 25
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
    Rectangle
    {
        id : confirmation
        opacity : 0
        width  : maxMenuWidth / 2
        height: maxMenuHeight / 1.5
        color : "blue"
        radius : 5
        anchors.horizontalCenter: parent.horizontalCenter
        Behavior on opacity {SmoothedAnimation {velocity : 1}}
        border
        {
            width: 2;
            color: "white"
        }
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
            font.pointSize: 17
        }
        // No buttom
        Rectangle
        {
            width: parent.width / 3
            height :  parent.height / 3
            color : "steelblue"
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
                font.pointSize: 15
            }
            border
            {
                width: 2;
                color: "white"
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
        Rectangle {
            width: parent.width / 3
            height :  parent.height / 3
            color : "steelblue"
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
                font.pointSize: 15
            }
            border
            {
                width: 2;
                color: "white"
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


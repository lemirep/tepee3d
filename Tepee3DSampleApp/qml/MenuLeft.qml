// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 2.0
import "js/Walls.js" as Walls;

Item
{
    id : menuLeftMain
    width: minMenuWidth
    height: minMenuHeight


    property bool isShown : false
    property int  minMenuWidth : mainWindow.menuMinimumWidth
    property int  maxMenuWidth : mainWindow.width / 3
    property int  minMenuHeight : mainWindow.height / 2
//    property int  minMenuHeight : mainWindow.height / 2
//    property int  minMenuHeight : mainWindow.height / 2
    //    property int  minMenuHeight : mainWindow.height
    property int  maxMenuHeight : mainWindow.height
    property int  xSaved;
    property int  savedWidth;
    property int  idx : 0;

    Component.onCompleted:
    {
        mainWindow.roomChanged.connect(setListIndex);
    }

    function startDrag(xPos, yPos)
    {
        xSaved = xPos;
        savedWidth = menuLeftMain.width
        console.log("xSaved " + xSaved);
    }

    function dragMoved(offsetX, offsetY)
    {
        var offset = offsetX;
        if ((savedWidth + offset) <=  maxMenuWidth &&
                (savedWidth + offset) >= minMenuWidth)
            menuLeftMain.width = savedWidth + offset;
    }

    function dragEnd()
    {
        if ((menuLeftMain.width - minMenuWidth) / maxMenuWidth > 0.4)
            menuLeftMain.isShown = true;
        else
            menuLeftMain.isShown = false;
        //        console.log(menuLeftMain.isShown)
    }

    function setListIndex(roomId)
    {
        var idx = roomModel.rowIndexFromId(roomId);
        rooms_list_view.currentIndex = idx;
    }

    states :     [
        State     {
            name: "menuShown"
            PropertyChanges
            {
                target: menuLeftMain;
                width : maxMenuWidth
                height : maxMenuHeight
            }
            PropertyChanges
            {
                target: menuLeftRec
                width : maxMenuWidth
                height : maxMenuHeight
                opacity : mainWindow.menu_opacity_deployed
            }
            PropertyChanges {
                target: add_room_button
                opacity : 1

            }
            PropertyChanges
            {
                target : rooms_list_view
                opacity : 1
            }
            when: menuLeftMain.isShown
        },
        State {
            name: "menuHidden"
            PropertyChanges
            {
                target: menuLeftMain
                width : minMenuWidth
                height : minMenuHeight
            }
            PropertyChanges {
                target: menuLeftRec
                width : minMenuWidth
                height : minMenuHeight
                opacity : 0.5
            }
            PropertyChanges {
                target: add_room_button
                opacity : 0
            }
            PropertyChanges
            {
                target : rooms_list_view
                opacity : 0
            }
            when: !menuLeftMain.isShown
        }]

    transitions :    [
        Transition
        {
            from: "menuHidden"
            to: "menuShown"
            NumberAnimation
            {
                target : menuLeftRec
                properties : "width, opacity"
                duration : 200
            }
            NumberAnimation
            {
                target : rooms_list_view
                properties : "opacity"
                duration : 250
            }

        },
        Transition
        {
            from: "menuShown"
            to: "menuHidden"
            NumberAnimation
            {
                target : menuLeftRec
                properties : "width, opacity"
                duration : 200
            }
            NumberAnimation
            {
                target : rooms_list_view
                properties: "opacity"
                duration : 150
            }
        }
    ]

    BorderImage
    {
        id : menuLeftRec
        height : parent.height
        width : parent.width
        //        color : mainWindow.menu_background_color
        opacity : 0
        source : "Resources/Pictures/panel_bg2.png"

        border
        {
            left : 2

            bottom : 1
        }

        ListView
        {
            id : rooms_list_view
            opacity : 0
            enabled : (opacity == 1)
            clip: true
            spacing: 10
            anchors
            {
                fill: parent
                margins : menuLeftMain.width / 8
            }
            orientation: ListView.Vertical
            model : roomModel
            delegate: RoomDelegate {
                width : menuLeftMain.width / 2;
                height : menuLeftMain.width / 3;
                roomId : model.roomId
                roomName : model.roomName
                roomScale : model.roomScale
                roomPosition : model.roomPosition
            }

            Component.onCompleted:{rooms_list_view.currentIndex = -1}

        }

        Image
        {
            id : add_room_button
            width : 50
            height : 50
            smooth : true
            scale : add_room_button_ma.pressed ? 0.9 : 1.0
            anchors
            {
                bottom : parent.bottom
                horizontalCenter : parent.horizontalCenter
            }
            MouseArea
            {
                id : add_room_button_ma
                anchors
                {
                    fill : parent
                }
                onClicked :
                {
                    roomManager.addNewRoom();
                }
            }

            source : "Resources/Pictures/add_button.svg"
        }
    }
}

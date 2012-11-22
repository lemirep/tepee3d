// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 2.0
import "testWalls.js" as Walls;

Item
{
    id : menuLeftMain
    width: minMenuWidth
    height: minMenuHeight


    property bool isShown : false
    property int  minMenuWidth : mainWindow.width / 10
    property int  maxMenuWidth : mainWindow.width / 3
    //    property int  minMenuHeight : mainWindow.height / 2
    property int  minMenuHeight : mainWindow.height
    property int  maxMenuHeight : mainWindow.height
    property int  xSaved;
    property int  savedWidth;
    property int  idx : 0;

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


    Rectangle
    {
        id : menuLeftRec
        height : parent.height
        width : parent.width
        color : mainWindow.menu_background_color
        opacity : 0


        ListView
        {
            id : rooms_list_view

            property real delegate_width :  menuLeftMain.width / 2;
            property real delegate_height : menuLeftMain.width / 3;
            property int  currentRoomId : -1;

            opacity : 0
            enabled : (opacity == 1)
            clip: true
            anchors
            {
                fill: parent
                margins : menuLeftMain.width / 8
            }
            orientation: ListView.Vertical
            model : roomModel
            delegate: room_list_delegate
            spacing: 10

            Component.onCompleted:
            {
                rooms_list_view.currentIndex = -1;
            }

            Timer
            {
                id : room_test_timer
                running : false
                interval : 1500
                repeat : true
                onTriggered:
                {
                    Walls.moveCameraToWall(camera, Walls.idx);
                    Walls.idx++;
                    Walls.idx %= Walls.walls.length;
                }
            }
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



    function setWalls(model)
    {
        Walls.idx = 0;
        Walls.currentWall = 0;
        Walls.walls = [];
        Walls.walls.push(model.roomNorthWallPosition);
        Walls.walls.push(model.roomSouthWallPosition);
        Walls.walls.push(model.roomEastWallPosition);
        Walls.walls.push(model.roomWestWallPosition);
        Walls.walls.push(model.roomUpWallPosition);
        Walls.walls.push(model.roomDownWallPosition);
        Walls.roomCenter = model.roomPosition;
        Walls.roomScale = model.roomScale;
        Walls.preComputeCenters();
    }




    Component
    {
        id : room_list_delegate
        Item
        {
            id : item_room_del
            width : rooms_list_view.delegate_width
            height : rooms_list_view.delegate_height
            anchors.horizontalCenter: parent.horizontalCenter
            scale : room_delegate_mouse_area.pressed ? 0.9 : 1.0


            MouseArea
            {
                id : room_delegate_mouse_area
                anchors.fill : parent
                onClicked :
                {
                    // SET CURRENT ROOM SELECTION
                    rooms_list_view.currentIndex = index
                    rooms_list_view.currentRoomId = model.roomId;
                    roomManager.setCurrentRoom(rooms_list_view.currentRoomId);
                    // LOAD WALLS DATA IN WALLS.js AND SET TOP MENU
                    camera_timer.stop();
                    setWalls(model);
                    topMenu.generateFaceModel();
                    // MOVE TO THE SELECTED ROOM
                    Walls.moveCameraToWall(camera, Walls.idx);
//                    room_test_timer.start();

                    console.log(model.roomId);
                    // SET MENU RIGHT PLUGIN MODEL
                    menuLeftMain.isShown = false;
                }
                onPressAndHold:
                {
                    if (rooms_list_view.currentRoomId == model.roomId)
                        rooms_list_view.currentIndex = -1;
                    roomManager.deleteRoom(model.roomId)
                }

            }

            Rectangle
            {
                color : (rooms_list_view.currentIndex == index) ? mainWindow.room_list_selected_component_color: mainWindow.room_list_component_color
                anchors.fill: parent

            }

            Text
            {
                id: room_title
                text: model.roomName
                anchors
                {
                    horizontalCenter : parent.horizontalCenter
                    bottom : parent.bottom
                    margins : 10
                }
                color :  "white"
            }
        }
    }



}

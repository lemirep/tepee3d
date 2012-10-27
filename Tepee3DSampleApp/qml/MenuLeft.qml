// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 2.0

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
                        rooms_list_view.currentIndex = index;
                        console.log(index);
                        console.log(rooms_list_view.currentIndex);
                        console.log("xc " + model.roomPosition.x + " yc " + model.roomPosition.y + " zc " + model.roomPosition.z);
                        // MOVE TO THE SELECTED ROOM
                        //camera.moveTo(model.roomPosition.x, model.roomPosition.y, model.roomPosition.z);

                        camera_timer.stop();


                        console.log("eyex " + model.roomPosition.x + " eyey " + model.roomPosition.y + " eyez " + model.roomPosition.z);
                        console.log("centerx " + model.roomCenter.x + " centery " + model.roomCenter.y + " centerz " + model.roomCenter.z);

                        camera.xCam = model.roomPosition.x;
                        camera.yCam = model.roomPosition.y;
                        camera.zCam = model.roomPosition.z - model.roomScale.z;

                        camera.xCamCenter = model.roomPosition.x;
                        camera.yCamCenter = model.roomPosition.y;
                        camera.zCamCenter = model.roomPosition.z;

                        roomManager.setCurrentRoom(model.roomId);
                        console.log(model.roomId);


                        // SET MENU RIGHT PLUGIN MODEL
                        rightMenu.currentRoomModel = null;

                        menuLeftMain.isShown = false;

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
}

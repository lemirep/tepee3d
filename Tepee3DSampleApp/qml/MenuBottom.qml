import QtQuick 2.0
import "content"

Item
{
    id : menuBottomMain
    width : minMenuWidth
    height : minMenuHeight

    property bool isShown : false
    property int  minMenuHeight : mainWindow.menuMinimumWidth
    property int  maxMenuHeight : mainWindow.height / 2
    property int  minMenuWidth : mainWindow.width / 2
    property int  maxMenuWidth : mainWindow.width
    property int  minMenuY : mainWindow.height - minMenuHeight
    property int  maxMenuY : mainWindow.height - maxMenuHeight
    property int  ySaved;
    property int  savedHeight;
    property alias pluginMenuSource : plugin_menu_loader.source

    Component.onCompleted:
    {
        mainWindow.roomFaceIdChanged.connect(setListIndex)
    }

    function startDrag(xPos, yPos)
    {
        ySaved = yPos;
    }

    function dragMoved(offsetX, offsetY)
    {
        var newY = offsetY + ySaved
        if (newY <= minMenuY && newY >= maxMenuY)
            savedHeight = mainWindow.height - newY;
    }

    function dragEnd()
    {
        if ((savedHeight - minMenuHeight) / maxMenuHeight > 0.4)
            menuBottomMain.isShown = true;
        else
            menuBottomMain.isShown = false;
    }

    function setListIndex(wallId)
    {
        console.log("Wall ID <><><><><><><><> " + wallId)
        room_faces_listview.currentIndex = wallId;
    }

    states : [
        State
        {
            name : "menuShown"
            PropertyChanges
            {
                target: menuBottomMain
                width : maxMenuWidth
                height : maxMenuHeight
                y : maxMenuY

            }
            PropertyChanges
            {
                target: menuBottomRec
                opacity : mainWindow.menu_opacity_deployed
            }
            when : menuBottomMain.isShown
        },
        State
        {
            name : "menuHidden"
            PropertyChanges
            {
                target: menuBottomMain
                width : minMenuWidth
                height : minMenuHeight
                y : minMenuY

            }
            PropertyChanges
            {
                target: menuBottomRec
                opacity : mainWindow.menu_opacity_retracted
            }
            when :!menuBottomMain.isShown
        }

    ]

    transitions : [
        Transition
        {
            from : "menuHidden"
            to : "menuShown"
        },
        Transition
        {
            from : "menuShown"
            to : "menuHidden"
        }
    ]

    BorderImage
    {
        id: menuBottomRec
        source: "Resources/Pictures/panel_bg2.png"
        width: parent.width; height: parent.height;
        border.left: 2; border.bottom: 1

        Loader
        {
            id : plugin_menu_loader
            anchors.fill: parent
            onLoaded:
            {
                "Menu Loaded"
            }
        }

        GridView
        {
            //            Rectangle
            //            {
            //                anchors.fill: parent
            //                color : "green"
            //            }

            id : room_faces_listview
            cellWidth: width / 6
            cellHeight: cellWidth
            //            property real delegate_width :  menuTopMain.height / 10;
            //            property real delegate_height : menuTopMain.height / 12;

            clip : true
            opacity :  0
            enabled : (opacity == 1)
            Behavior on opacity {NumberAnimation {duration : 500}}

            anchors
            {
                left : parent.left
                top : parent.top
                bottom : parent.bottom
                right : parent.right
                margins : menuBottomRec.height / 8
            }

            delegate : room_face_view_delegate
            model : currentRoomFacesModel
            Component.onCompleted:
            {
                room_faces_listview.currentIndex = -1;
            }
        }



        Component
        {
            id : room_face_view_delegate
            Item
            {
                id : room_face_del_item
                width : room_faces_listview.cellWidth
                height : room_faces_listview.cellHeight
                // anchors.verticalCenter: parent.verticalCenter
                scale : room_face_delegate_mouse_area.pressed ? 0.9 : 1.0
                MouseArea
                {
                    id : room_face_delegate_mouse_area
                    anchors.fill : parent
                    onClicked :
                    {
                        room_faces_listview.currentIndex = index
                        //                        moveToFace(model.idx)
                        mainWindow.currentRoomFaceId = index;
                    }
                }

                Rectangle
                {
                    color : (room_faces_listview.currentIndex == index) ? mainWindow.room_list_selected_component_color: mainWindow.room_list_component_color
                    anchors.fill: parent
                    anchors.margins: 10
                }

                Text
                {
                    anchors
                    {
                        centerIn : parent
                    }
                    text : model.name
                }
            }

        }
        Text
        {

            text : getTime();

            Timer
            {
                running: true
                interval : 60000
                onTriggered:
                {
                    parent.text = parent.getTime();
                }
            }


            function getTime()
            {
                var d = new Date();
                return d.getHours() + ":" + d.getMinutes();
            }

            color : "white"
            anchors
            {
                top : parent.top
                horizontalCenter : parent.horizontalCenter
                margins : 10
            }
        }
        Rectangle {
            width: 600; height: 240
            color: "#646464"
            opacity:0.75
            anchors
            {
                top : parent.top
                horizontalCenter : parent.horizontalCenter
                margins : 80
            }
            Row {
                anchors.centerIn: parent
                Clock { city: "New York"; shift: -4 }
                Clock { city: "Paris"; shift: 2 }
                Clock { city: "Tokyo"; shift: 9 }
            }

            //   QuitButton {
            //     anchors.right: parent.right
            //   anchors.top: parent.top
            // anchors.margins: 10
            //}
        }

    }
}

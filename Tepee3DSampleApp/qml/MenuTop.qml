// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 2.0
import "testWalls.js" as Walls;

Item
{
    id : menuTopMain
    width: minMenuWidth
    height: minMenuHeight
    property bool isShown : false
    property int  minMenuHeight : mainWindow.height / 10
    property int  maxMenuHeight : mainWindow.height / 2
    property int  minMenuWidth : mainWindow.width / 2
    property int  maxMenuWidth : mainWindow.width
    property int  ySaved;
    property int  savedHeight;

    ListModel
    {
        id : room_faces_model
    }

    function generateFaceModel()
    {
        Walls.generateWallFacesModel(room_faces_model);
    }

    function startDrag(xPos, yPos)
    {
        ySaved = yPos;
        savedHeight = menuTopMain.height
    }

    function dragMoved(offsetX, offsetY)
    {
        var offset = offsetY;
        if ((savedHeight + offset) <=  maxMenuHeight &&
                (savedHeight + offset) >= minMenuHeight)
            menuTopMain.height = savedHeight + offset;
    }

    function  dragEnd()
    {
        if ((menuTopMain.height - minMenuHeight) / maxMenuHeight > 0.4)
        {
            if (menuTopMain.isShown)
                menuTopMain.isShown = false;
            menuTopMain.isShown = true;
        }
        else
        {
            if (!menuTopMain.isShown)
                menuTopMain.isShown = true;
            menuTopMain.isShown = false;
        }
    }

    states :     [
        State     {
            name: "menuShown"
            PropertyChanges
            {
                target: menuTopMain;
                height : maxMenuHeight
                width : maxMenuWidth
            }
            PropertyChanges
            {
                target: menuTopRec
                height : maxMenuHeight
                width : maxMenuWidth
                opacity : mainWindow.menu_opacity_deployed
            }
            PropertyChanges
            {
                target : room_faces_listview
                opacity : 1
            }
            when: menuTopMain.isShown
        },
        State {
            name: "menuHidden"
            PropertyChanges
            {
                target: menuTopMain
                height : minMenuHeight
                width : minMenuWidth
            }
            PropertyChanges
            {
                target: menuTopRec
                opacity : 0
            }
            PropertyChanges
            {
                target : room_faces_listview
                opacity : 0
            }
            when: !menuTopMain.isShown
        }]

//    transitions :[
//        Transition
//        {
//            from: "menuHidden"
//            to: "menuShown"
//            NumberAnimation
//            {
//                target : menuTopRec
//                properties : "width, height, opacity"
//                duration : 200
//            }
//            NumberAnimation
//            {
//                target : room_faces_listview
//                properties : "opacity"
//                duration : 250
//            }
//        },
//        Transition
//        {
//            from: "menuHidden"
//            to: "menuShown"
//            NumberAnimation
//            {
//                target : menuTopRec
//                properties : "width, height, opacity"
//                duration : 200
//            }
//            NumberAnimation
//            {
//                target : room_faces_listview
//                properties : "opacity"
//                duration : 250
//            }
//        }
//    ]

    Rectangle
    {
        id : menuTopRec
        width : parent.width
        height : parent.height
        color : mainWindow.menu_background_color
        opacity : 0
//        Behavior on height {NumberAnimation {duration: 100}}
//        Behavior on width {PropertyAnimation { properties: "width"; easing.type: Easing.OutBounce; duration : 500 }}
//        Behavior on opacity {NumberAnimation {duration: 500}}

        ListView
        {
            id : room_faces_listview
            property real delegate_width :  menuTopMain.height / 2;
            property real delegate_height : menuTopMain.height / 3;

            clip : true
            opacity :  0
            enabled : (opacity == 1)
            Behavior on opacity {NumberAnimation {duration : 500}}
            anchors
            {
                fill : parent
                margins : menuTopRec.height / 8
            }
            orientation : ListView.Horizontal
            spacing : 10
            delegate : room_face_view_delegate
            model : room_faces_model
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
                width : room_faces_listview.delegate_width
                height : room_faces_listview.delegate_height
                anchors.verticalCenter: parent.verticalCenter
                scale : room_face_delegate_mouse_area.pressed ? 0.9 : 1.0

                MouseArea
                {
                    id : room_face_delegate_mouse_area
                    anchors.fill : parent
                    onClicked :
                    {
                        room_faces_listview.currentIndex = index
                        menuTopMain.isShown = false;
                        Walls.moveCameraToWall(camera, model.idx);
                    }
                }

                Rectangle
                {
                    color : (room_faces_listview.currentIndex == index) ? mainWindow.room_list_selected_component_color: mainWindow.room_list_component_color
                    anchors.fill: parent

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
                bottom : parent.bottom
                horizontalCenter : parent.horizontalCenter
                margins : 10
            }
        }
    }

}

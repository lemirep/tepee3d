// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 2.0

Item
{
    id : menuTopMain
    width: minMenuWidth
    height: minMenuHeight
    property bool isShown : false
    property int  minMenuHeight : mainWindow.menuMinimumWidth
    property int  maxMenuHeight : mainWindow.height / 2
    property int  minMenuWidth : mainWindow.width / 2
    property int  maxMenuWidth : mainWindow.width
    property int  ySaved;
    property int  savedHeight;
    property bool isPressed;

    Component.onCompleted:    {mainWindow.roomFaceIdChanged.connect(setListIndex)}

    function startDrag(xPos, yPos)    {ySaved = yPos;savedHeight = menuTopMain.height}

    function dragMoved(offsetX, offsetY)
    {
        var offset = offsetY;
        if ((savedHeight + offset) <=  maxMenuHeight &&
                (savedHeight + offset) >= minMenuHeight)
            menuTopMain.height = savedHeight + offset;
        if ((menuTopMain.height - minMenuHeight) / maxMenuHeight > 0.4)
            menuTopMain.isShown = true;
        else
            menuTopMain.isShown = false;
    }

    function  dragEnd()
    {
        var oldstate = menuTopMain.isShown
        if ((menuTopMain.height - minMenuHeight) / maxMenuHeight > 0.4)
            menuTopMain.isShown = true;
        else
            menuTopMain.isShown = false;
        if (oldstate == menuTopMain.isShown)
        {
            menuTopMain.state = ""
            menuTopMain.state = (oldstate) ? "menuShown" : "menuHidden"
        }
    }

    function setListIndex(wallId)    {room_faces_listview.currentIndex = wallId;}

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
                target : arrow_image
                opacity : 0
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
                opacity : mainWindow.menu_opacity_retracted
            }           
            PropertyChanges
            {
                target : arrow_image
                opacity : 0.8
            }
            when: !menuTopMain.isShown
        }]

    transitions :    [
        Transition
        {
            from: "menuHidden"
            to: "menuShown"
            NumberAnimation
            {
                target : menuTopRec
                properties : "height, opacity"
                duration : 200
            }
        },
        Transition
        {
            from: "menuShown"
            to: "menuHidden"
            NumberAnimation
            {
                target : menuTopRec
                properties : "height, opacity"
                duration : 200
            }
        }
    ]


    BorderImage
    {
        id : menuTopRec
//            width : parent.width
//            height : parent.height
        anchors.fill: parent
        source : "../Resources/Pictures/panel_bg2.png"
        //        color : mainWindow.menu_background_color
        opacity : 0
        //        Behavior on height {NumberAnimation {duration: 100}}
        //        Behavior on width {PropertyAnimation { properties: "width"; easing.type: Easing.OutBounce; duration : 500 }}
        //        Behavior on opacity {NumberAnimation {duration: 500}}

        border
        {
            left : 2
            bottom : 1
        }


        GridView
        {
            id : room_faces_listview
            cellWidth: width / 6
            cellHeight: cellWidth
            //            property real delegate_width :  menuTopMain.height / 10;
            //            property real delegate_height : menuTopMain.height / 12;

            clip : true
            opacity :  (menuTopRec.height == maxMenuHeight) ? 1 : 0
            enabled : (opacity == 1)
            Behavior on opacity {SmoothedAnimation {velocity : 1}}

            anchors
            {
                left : parent.left
                top : parent.top
                bottom : parent.bottom
                right : parent.right
                margins : menuTopRec.height / 8
            }

            delegate : room_face_view_delegate
            model : currentRoomFacesModel
            Component.onCompleted:    {room_faces_listview.currentIndex = -1;}
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
                    anchors.centerIn : parent
                    text : model.name
                }
            }
        }
    }
    Image
    {
        id : arrow_image
        anchors.centerIn: parent
        source : "../Resources/Pictures/arrow.png"
        fillMode: Image.PreserveAspectFit
        Behavior on opacity {SmoothedAnimation {velocity : 10}}
        height : mainWindow.menuMinimumWidth
        scale : isPressed ? 0.9 :  1
    }
}

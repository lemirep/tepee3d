// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 2.1
import QtGraphicalEffects 1.0

Item
{
    id : menuLeftMain
    width: minMenuWidth
    height: minMenuHeight


    property bool isShown : false
    property int  minMenuWidth : mainWindow.menuMinimumWidth
    property int  maxMenuWidth : mainWindow.width / 3
    property int  minMenuHeight : mainWindow.height
    property int  maxMenuHeight : mainWindow.height
    property int  offsetSaved;
    property int  savedWidth;
    property int  idx : 0;
    property bool isPressed;
    property bool isInEditMode : false;

    Behavior on width {NumberAnimation {duration : 200}}

    Component.onCompleted:    {mainWindow.roomChanged.connect(setListIndex);}
    onIsShownChanged:    {isInEditMode = false; menuLeftMain.width = (isShown) ? maxMenuWidth : minMenuWidth}

    function startDrag(xPos, yPos)    {savedWidth = menuLeftMain.width}

    function dragMoved(offsetX, offsetY)
    {
        if ((savedWidth + offsetX) <=  maxMenuWidth &&
                (savedWidth + offsetX) >= minMenuWidth)
            menuLeftMain.width = savedWidth + offsetX;
        offsetSaved = offsetX
    }

    function dragEnd()
    {
        var oldState = menuLeftMain.isShown
        var deployed = (menuLeftMain.width - minMenuWidth) / maxMenuWidth > 0.4
        var dragLength = 30

        if (offsetSaved > dragLength)
            menuLeftMain.isShown = true
        else if (offsetSaved < -dragLength)
            menuLeftMain.isShown = false
        else
            menuLeftMain.isShown = deployed
        if (oldState === menuLeftMain.isShown)
            menuLeftMain.width = (menuLeftMain.isShown) ? maxMenuWidth : minMenuWidth;
    }

    function setListIndex(roomId)
    {
        var idx = roomModel.rowIndexFromId(roomId);
        rooms_list_view.currentIndex = idx;
    }

    function disableMenuButtons()
    {
        sky_room_view_button.enabled = false;
        add_room_button.enabled = false;
        edit_image_button.enabled = false;
        rooms_list_view.lockList = true;
    }

    function enableMenuButtons()
    {
        sky_room_view_button.enabled = true;
        add_room_button.enabled = true;
        edit_image_button.enabled = true;
        rooms_list_view.lockList = false;
    }

    states : [
        State
        {
            name : "menuShown"
            PropertyChanges    {target: menuLeftRec; opacity :  menu_opacity_deployed}
            PropertyChanges    {target: edit_image_button; opacity : 1}
            PropertyChanges    {target: add_room_button; opacity : 1}
            PropertyChanges    {target: sky_room_view_button; opacity : 1}
            PropertyChanges    {target: arrow_image; opacity : 0}
            when : menuLeftMain.isShown || ((menuLeftMain.width - minMenuWidth) / maxMenuWidth > 0.4)
        },
        State
        {
            name : "menuHidden"
            PropertyChanges    {target: menuLeftRec; opacity :  menu_opacity_retracted}
            PropertyChanges    {target: add_room_button; opacity : 0}
            PropertyChanges    {target: edit_image_button; opacity : 0}
            PropertyChanges    {target: add_room_button; opacity : 0}
            PropertyChanges    {target: sky_room_view_button; opacity : 0}
            PropertyChanges    {target: arrow_image; opacity : 0.8}
            when : !menuLeftMain.isShown || !((menuLeftMain.width - minMenuWidth) / maxMenuWidth > 0.4)
        }
    ]

    transitions : [
        Transition
        {
            NumberAnimation    {target : menuLeftRec; properties : "opacity"; duration : 200}
        }
    ]


    Item
    {
        id : menuLeftRec
        anchors.fill: parent

        BorderImage
        {
            id : menu_back_img
            anchors.fill: parent
            source : "../Resources/Pictures/panel_bg2.png"
            border
            {
                left : 2
                bottom : 1
            }
            opacity : 0.7
            //            ZoomBlur    {opacity: isShown ? 1 : 0; anchors.fill: menu_back_img; source : menu_back_img; samples : 24; length : 48}
        }

        ListView
        {
            id : rooms_list_view
            property bool lockList : false;

            opacity : (menuLeftRec.width === maxMenuWidth) ? 1 : 0
            Behavior on opacity {SmoothedAnimation {velocity : 1}}
            enabled : (opacity === 1 && menuLeftRec.width === maxMenuWidth && !lockList)
            clip: true
            spacing: 10
            width : menuLeftMain.width / 2;
            anchors
            {
                horizontalCenter : parent.horizontalCenter
                top : parent.top
                bottom : parent.bottom
                topMargin : menuLeftMain.width / 8
                bottomMargin : menuLeftMain.width / 8
            }
            orientation: ListView.Vertical
            model : roomModel
            delegate: RoomDelegate {
                width : rooms_list_view.width;
                height : menuLeftMain.width / 3;
                roomId : model.roomId
                roomName : model.roomName
                roomScale : model.roomScale
                roomPosition : model.roomPosition
                editMode: isInEditMode
            }
            Component.onCompleted:{rooms_list_view.currentIndex = -1}

            // Transition to apply to items that are removed
            remove : Transition {
                ParallelAnimation
                {
                    SmoothedAnimation {property : "x"; to : 400; duration : 200}
                    NumberAnimation {property : "opacity"; to : 0; duration : 1200}
                }
            }
            // Transition to apply to items that are added
            add : Transition {
                SequentialAnimation
                {
                    ParallelAnimation
                    {
                        NumberAnimation {property : "x"; to : -400; duration : 0}
                        NumberAnimation {property : "opacity"; to : 0; duration : 0}
                    }
                    ParallelAnimation
                    {
                        SmoothedAnimation {property : "x"; to : 0; duration : 200}
                        NumberAnimation {property : "opacity"; to : 1; duration : 1200}
                    }
                }
            }

            addDisplaced: add_remove_displaced_transition
            removeDisplaced : add_remove_displaced_transition
            // Transition to apply to items displaced by addition or removal of items
            Transition
            {
                id : add_remove_displaced_transition
                SmoothedAnimation {property : "y"; duration : 500}
            }


        }

        Image
        {
            id : sky_room_view_button
            width : 50
            height : 50
            scale : sky_view_button_ma.pressed ? 0.9 : 1.0
            anchors    {bottom : parent.bottom; right: add_room_button.left}
            source : "../Resources/Pictures/round.png"
            MouseArea
            {
                id : sky_view_button_ma
                anchors.fill: parent
                onClicked:    {mainWindow.currentRoomId = -1; mainWindow.moveCameraToSkyView(); leftMenu.isShown = false}
            }
        }

        Image
        {
            id : add_room_button
            width : 50
            height : 50
            smooth : true
            scale : add_room_button_ma.pressed ? 0.9 : 1.0
            anchors    {bottom : parent.bottom; horizontalCenter : parent.horizontalCenter}
            MouseArea
            {
                id : add_room_button_ma
                anchors.fill : parent
                onClicked :
                {
                    mainWindow.currentRoomId = -1;
                    mainWindow.moveCameraToSkyView();

                    var jsonMessage = {message : "newWindow Added", type : 0, callback : { func : testCallback, context : this}};
                    mainWindow.postNotification(jsonMessage);
                    //                    mainWindow.postNotification(jsonMessage);
                    //                    mainWindow.postNotification(jsonMessage);
                    //                    mainWindow.postNotification(jsonMessage);
                    // DISABLE BUTTON WHILE WAITING FOR CALLBACK
                    //                    disableMenuButtons();

                    function testCallback()
                    {
                        console.log("CallBACK " + add_room_button.width);
                        // RESTORE BUTTONS ON CALLBACK
                        enableMenuButtons();
                    }

                    roomManager.addNewRoom();
                }
            }
            source : "../Resources/Pictures/plus.png"
        }

        Image
        {
            id : edit_image_button
            width : 50
            rotation: 45
            scale : (edit_image_ma.pressed) ? 0.9 : 1
            fillMode: Image.PreserveAspectFit
            anchors {bottom : parent.bottom; left : add_room_button.right}
            MouseArea
            {
                id : edit_image_ma; anchors.fill: parent;
                onClicked: {isInEditMode = !isInEditMode}
            }
            source : "../Resources/Pictures/edit.png"
        }
    }

    Image
    {
        id : arrow_image
        anchors.centerIn: parent
        source : "../Resources/Pictures/arrow.png"
        fillMode: Image.PreserveAspectFit
        Behavior on opacity {SmoothedAnimation {velocity : 10}}
        rotation : -90
        height : mainWindow.menuMinimumWidth
        scale : isPressed ? 0.9 :  1
    }
}

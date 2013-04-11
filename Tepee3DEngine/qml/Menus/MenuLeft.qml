// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 2.0

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
    property bool isPressed;
    property bool isInEditMode : false;


    Component.onCompleted:    {mainWindow.roomChanged.connect(setListIndex);}
    onIsShownChanged:    {isInEditMode = false}

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
        if ((menuLeftMain.width - minMenuWidth) / maxMenuWidth > 0.4)
            menuLeftMain.isShown = true;
        else
            menuLeftMain.isShown = false;
    }

    function dragEnd()
    {
        var oldstate = menuLeftMain.isShown
        if ((menuLeftMain.width - minMenuWidth) / maxMenuWidth > 0.4)
            menuLeftMain.isShown = true;
        else
            menuLeftMain.isShown = false;
        if (oldstate == menuLeftMain.isShown)
        {
            menuLeftMain.state = ""
            menuLeftMain.state = (oldstate) ? "menuShown" : "menuHidden"
        }
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

    states :     [
        State     {
            name: "menuShown"
            PropertyChanges    {target: menuLeftMain; width : maxMenuWidth; height : maxMenuHeight}
            PropertyChanges    {target: menuLeftRec; width : maxMenuWidth; height : maxMenuHeight; opacity : mainWindow.menu_opacity_deployed}
            PropertyChanges    {target: add_room_button; opacity : 1}
            PropertyChanges    {target: arrow_image; opacity : 0}
            when: menuLeftMain.isShown
        },
        State {
            name: "menuHidden"
            PropertyChanges    {target: menuLeftMain; width : minMenuWidth; height : minMenuHeight}
            PropertyChanges {target: menuLeftRec; width : minMenuWidth; height : minMenuHeight; opacity : mainWindow.menu_opacity_retracted}
            PropertyChanges {target: add_room_button; opacity : 0}
            PropertyChanges    {target: arrow_image; opacity : 0.8}
            when: !menuLeftMain.isShown
        }]

    transitions :    [
        Transition
        {
            from: "menuHidden"
            to: "menuShown"
            SmoothedAnimation    {target : menuLeftRec; properties : "width, opacity"; duration : -1; velocity : 1}
        },
        Transition
        {
            from: "menuShown"
            to: "menuHidden"
            SmoothedAnimation    {target : menuLeftRec; properties : "width, opacity"; duration : 200; velocity : 50}
        }
    ]

    BorderImage
    {
        id : menuLeftRec
        anchors.fill: parent
        opacity : 0
        source : "../Resources/Pictures/panel_bg2.png"

        border
        {
            left : 2
            bottom : 1
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
                editMode: isInEditMode
            }
            Component.onCompleted:{rooms_list_view.currentIndex = -1}
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

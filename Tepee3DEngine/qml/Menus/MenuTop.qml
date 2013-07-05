// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 2.0
import "../content"
Item
{
    id : menuTopMain
    width: minMenuWidth
    height: minMenuHeight
    property bool isShown : false
    property int  minMenuHeight : mainWindow.menuMinimumWidth
    property int  maxMenuHeight : mainWindow.height / 2
    property int  minMenuWidth : mainWindow.width
    property int  maxMenuWidth : mainWindow.width
    property int  offsetSaved;
    property int  savedHeight;
    property bool isPressed;

    Component.onCompleted:    {mainWindow.roomFaceIdChanged.connect(setListIndex);}
    onIsShownChanged: {menuTopMain.height = (menuTopMain.isShown) ? maxMenuHeight : minMenuHeight}

    Behavior on height {NumberAnimation {duration : 200}}

    function startDrag(xPos, yPos)    {savedHeight = menuTopMain.height}

    function dragMoved(offsetX, offsetY)
    {
        if ((savedHeight + offsetY) <=  maxMenuHeight &&
                (savedHeight + offsetY) >= minMenuHeight)
            menuTopMain.height = savedHeight + offsetY;
        offsetSaved = offsetY;
    }

    function  dragEnd()
    {
        var oldstate = menuTopMain.isShown
        var deployed = (menuTopMain.height - minMenuHeight) / maxMenuHeight > 0.4
        var dragLength = 30

        if (offsetSaved > dragLength)
            menuTopMain.isShown = true
        else if (offsetSaved < -dragLength)
            menuTopMain.isShown = false
        else
            menuTopMain.isShown = dragLength
        if (oldstate === menuTopMain.isShown)
            menuTopMain.height = (menuTopMain.isShown) ? maxMenuHeight : minMenuHeight
    }

    function setListIndex(wallId)    {room_faces_listview.currentIndex = wallId;}

    states :     [
        State     {
            name: "menuShown"
            PropertyChanges    {target: menuTopRec; opacity : mainWindow.menu_opacity_deployed}
            PropertyChanges    {target : arrow_image; opacity : 0}
            when: menuTopMain.isShown || ((menuTopMain.height - minMenuHeight) / maxMenuHeight > 0.4)
        },
        State {
            name: "menuHidden"
            PropertyChanges    {target: menuTopRec; opacity : mainWindow.menu_opacity_retracted}
            PropertyChanges    {target : arrow_image; opacity : 0.8}
            when: !menuTopMain.isShown || !((menuTopMain.height - minMenuHeight) / maxMenuHeight > 0.4)
        }]

    transitions :    [
        Transition
        {
            NumberAnimation    {target : menuTopRec; properties : "opacity"; duration : 200}
        }
    ]

    BorderImage
    {
        id : menuTopRec
        anchors.fill: parent
        source : "../Resources/Pictures/panel_bg2.png"
        opacity : 0
        border
        {
            left : 2
            bottom : 1
        }
        QuitButton
        {
            anchors
            {
                left : room_faces_listview.right
                leftMargin : maxMenuWidth / 8
                right: parent.right
                rightMargin: maxMenuWidth / 8
                top :parent.top
                topMargin : maxMenuHeight / 5
                bottom : parent.bottom
                //verticalCenter: parent.verticalCenter
            }
        }
        GridView
        {
            id : room_faces_listview
            cellWidth: width / 3
            cellHeight: height / 2

            clip : true
            opacity :  (menuTopRec.height == maxMenuHeight && mainWindow.currentRoomId != -1) ? 1 : 0
            enabled : (opacity == 1)
            Behavior on opacity {SmoothedAnimation {velocity : 1}}

            anchors
            {
                left : parent.left
                top : parent.top
                bottom : parent.bottom
                right : parent.horizontalCenter
                margins : menuTopRec.height / 8
            }

            delegate : RoomMenuFaceDelegate {roomName : model.name}
            model : currentRoomFacesModel
            Component.onCompleted:    {room_faces_listview.currentIndex = -1;}
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

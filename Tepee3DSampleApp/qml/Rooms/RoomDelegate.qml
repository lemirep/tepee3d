import QtQuick 2.0


Item
{
    id : item_room_del
    width : rooms_list_view.delegate_width
    height : rooms_list_view.delegate_height

    property int      roomId : 0
    property int      isSelected : rooms_list_view.currentIndex === index
    property string   roomName : ""
    property vector3d roomPosition : Qt.vector3d(0, 0, 0)
    property vector3d roomScale : Qt.vector3d(0, 0, 0)

    anchors.horizontalCenter: parent.horizontalCenter
    scale : room_delegate_mouse_area.pressed ? 0.9 : 1.0

    Behavior on scale {SmoothedAnimation {velocity : 1; duration : -1}}

    MouseArea
    {
        id : room_delegate_mouse_area
        anchors.fill : parent
        onClicked :
        {
            // SET CURRENT ROOM SELECTION
            mainWindow.currentRoomId = model.roomId
            menuLeftMain.isShown = false;
        }
        onPressAndHold:
        {
            if (isSelected)
                mainWindow.postNotification("Cannot remove a Room when your are currently in it!");
//                rooms_list_view.currentIndex = -1;
            else
                roomManager.deleteRoom(model.roomId)
            //            console.log("start animation")
            //            anim.start();
        }
    }

    SequentialAnimation
    {
        id : anim
        PropertyAnimation {
            target: delRect
            property: "rotation"
            to : 5
            duration: 200
        }
        PropertyAnimation {
            target: delRect
            property: "rotation"
            to : -5
            duration: 200
        }
        PropertyAnimation {
            target: delRect
            property: "rotation"
            to : 0
            duration: 200
        }
        loops: Animation.Infinite
    }

    BorderImage
    {
        id: delRect
        source: (rooms_list_view.currentIndex === index) ? "../Resources/Pictures/delegate_selected.png" : "../Resources/Pictures/delegate.png"
        anchors.fill: parent
        Behavior on rotation {SpringAnimation {spring: 30; damping: 0.3; mass: 1.0}}
    }

    Text
    {
        id: room_title
        text: roomName
        anchors.centerIn : delRect
        color :  "white"
    }
}

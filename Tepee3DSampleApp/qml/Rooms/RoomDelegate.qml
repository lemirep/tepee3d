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
        text: roomName
        anchors
        {
            horizontalCenter : parent.horizontalCenter
            bottom : parent.bottom
            margins : 10
        }
        color :  "white"
    }
}

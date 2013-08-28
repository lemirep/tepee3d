import QtQuick 2.1

Item
{
    id : room_face_del_item
    width : room_faces_listview.cellWidth
    height : room_faces_listview.cellHeight
    scale : room_face_delegate_mouse_area.pressed ? 0.9 : 1.0
    Behavior on scale {SmoothedAnimation {velocity : 1; duration : -1}}
    property string roomName;

    MouseArea
    {
        id : room_face_delegate_mouse_area
        anchors.fill : parent
        onClicked :
        {
            room_faces_listview.currentIndex = index
            mainWindow.currentRoomFaceId = index;
        }
    }

    BorderImage
    {
        id: delRect
        source: (room_faces_listview.currentIndex === index) ? "../Resources/Pictures/delegate_selected.png" : "../Resources/Pictures/delegate.png"
        anchors.fill: parent
    }

    Text
    {
        anchors.centerIn : parent
//        width : delRect.width
        font.pixelSize: mainWindow.defaultFontSize
        elide : Text.ElideMiddle
        text : roomName
        color :  "white"
    }
}

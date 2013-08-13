import QtQuick 2.1


Item
{
    id : item_room_del

    property int      roomId : 0
    property int      isSelected : rooms_list_view.currentIndex === index
    property string   roomName : ""
    property vector3d roomPosition : Qt.vector3d(0, 0, 0)
    property vector3d roomScale : Qt.vector3d(0, 0, 0)
    property bool     editMode;

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
    }


    states : [
        State
        {
            name : "viewMode"
            when : !editMode
            PropertyChanges    {target : delete_room_button; opacity : 0}
            PropertyChanges    {target : room_delegate_mouse_area; enabled : true}
            PropertyChanges    {target : editAnimation; running : false}
        },

        State
        {
            name : "editMode"
            when : editMode
            PropertyChanges    {target : delete_room_button; opacity : 1}
            PropertyChanges    {target : room_delegate_mouse_area; enabled : false}
            PropertyChanges    {target : editAnimation; running : true}
        }
    ]


    SequentialAnimation
    {
        id : editAnimation
        PropertyAnimation {
            target: delRect
            property: "rotation"
            to : 5
            duration: 400
        }
        PropertyAnimation {
            target: delRect
            property: "rotation"
            to : -5
            duration: 400
        }
        //        PropertyAnimation {
        //            target: delRect
        //            property: "rotation"
        //            to : 0
        //            duration: 200
        //        }
        loops: Animation.Infinite
        onRunningChanged: {delRect.rotation = 0}
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

    Image
    {
        id : delete_room_button
        width : 50
        scale : (delete_button_ma.pressed) ? 0.9 : 1
        fillMode: Image.PreserveAspectFit
        anchors
        {
            right : parent.right
            bottom : parent.bottom
        }
        source : "../Resources/Pictures/red_cross.png";
        MouseArea
        {
            id : delete_button_ma;anchors.fill: parent
            enabled : (delete_room_button.opacity == 1)
            onClicked:
            {
                if (isSelected)
                {
                    var jsonMessage = {message : "Cannot remove the room while you're in it !", type : 2, callback : { func : function() {}, context : this}};
                    mainWindow.postNotification(jsonMessage);
                }
                else
                    roomManager.deleteRoom(model.roomId)
            }
        }
    }
}

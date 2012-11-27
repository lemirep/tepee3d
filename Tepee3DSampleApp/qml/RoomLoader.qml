import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0

Item3D
{
    id : room_loader_item
    property alias source : room_loader.source
    property variant widgetsModel : null
    property vector3d roomPosition : Qt.vector3d(0, 0, 0)
    property vector3d roomScale : Qt.vector3d(0, 0, 0)

//    objectName : "item3dOfRoomLoader"

    Loader
    {
        id : room_loader
        function getPosition() {console.log("----++RoomPosition");return room_loader_item.roomPosition}
        function getScale()    {console.log("====++RoomScale");return room_loader_item.roomScale}
        function getWidgetsModel() {return room_loader_item.widgetsModel}

        onLoaded:
        {
            console.log("Room Loaded");
        }
        onProgressChanged:
        {
            console.log("-----------Progress Changed");
        }
    }
//        Room
//        {
//            id : room
//            position : room_loader_item.roomPosition
//            transform : [ Scale3D { scale : room_loader_item.roomScale}]

//            onClicked :
//            {
//                console.log("RoomPress");
//            }

//            onPositionChanged :
//            {
//                console.log(position);
//            }
//        }
}

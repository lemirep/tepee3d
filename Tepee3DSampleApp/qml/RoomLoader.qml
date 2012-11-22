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

    Loader
    {
        id : room_loader
        function getPosition() {return room_loader_item.roomPosition}
        function getScale()    {return room_loader_item.roomScale}
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
}

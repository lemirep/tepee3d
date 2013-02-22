import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0

Item3D
{
    id : room_loader_item
    property int roomId : -1
    property alias source : room_loader.source
    property variant widgetsModel : null
    property vector3d roomPosition : Qt.vector3d(0, 0, 0)
    property vector3d roomScale : Qt.vector3d(0, 0, 0)

    Loader
    {
        id : room_loader
        onLoaded:        {}
        onProgressChanged:        {}
    }
}


import QtQuick 2.0
import Qt3D 2.0

Item3D
{
    Repeater
    {
        model : roomModel
        delegate : roomDelegate
        objectName : "repeaterMain"
    }

    Component                   // NOT WORKING YET -> Qt5 Bug should be resolved by release version
    {                           // https://bugreports.qt-project.org/browse/QTBUG-27444
        id : roomDelegate

        RoomLoader              // LOAD THE ROOM QML FILE SPECIFIED IN THE MODEL
        {                       // QT BUG NOT WORKING YET
            id : room_loader
            roomPosition : model.roomPosition
            roomScale : model.roomScale
            widgetsModel : currentRoomPluginsModel
            source : "Room.qml"
        }
    }
}

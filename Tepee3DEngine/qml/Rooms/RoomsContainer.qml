import QtQuick 2.1
import Qt3D 2.0

Item3D
{
    ListView
    {
        model : roomModel
        delegate : roomDelegate
    }

    Component                   // NOT WORKING YET -> Qt5 Bug should be resolved by release version
    {                           // https://bugreports.qt-project.org/browse/QTBUG-27444
        id : roomDelegate
        RoomLoader              // LOAD THE ROOM QML FILE SPECIFIED IN THE MODEL
        {                       // QT BUG NOT WORKING YET
            id : room_loader
            roomId : model.roomId
            roomScale : model.roomScale
            roomPosition : model.roomPosition
            widgetsModel : roomModel.subModelFromId(model.roomId)
            source : "Room.qml"
        }
    }
}

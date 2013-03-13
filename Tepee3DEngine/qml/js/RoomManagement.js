.pragma library

.import "Walls.js" as Walls

var roomModel;

function initialize(camera_, roomModel_, faceModel_)
{
    roomModel = roomModel_;
    Walls.initialize(camera_, faceModel_)
}

function findRoomInModel(roomId)
{
    if (roomId >= 0)
        for (var i = 0; i < roomModel.count; i++)
            if (roomModel.get(i).roomId === roomId)
                return roomModel.get(i);
    return null;
}

function moveToRoom(roomProperties)
{
    if (roomProperties)
    {
        setWalls(roomProperties.roomPosition, roomProperties.roomScale);
        Walls.generateWallFacesModel()
        Walls.moveCameraToWall(Walls.idx)
    }
}

function setWalls(roomPosition, roomScale)
{
    Walls.idx = 0;
    Walls.currentWall = 0;
    Walls.roomCenter = roomPosition;
    Walls.roomScale = roomScale;
    Walls.preComputeWalls();
    Walls.preComputeCenters();
}

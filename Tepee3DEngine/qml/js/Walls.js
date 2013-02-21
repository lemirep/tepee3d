.pragma library


// THERE ARE 6 WALLS WHICH WHICH BE SAVED IN THE FOLLOWING ORDER
// NORTH, SOUTH, EAST, WEST, UP, DOWN

var walls = new Array();
var computedCenters = null;
var facesNames = ["North", "South", "East", "West", "Down", "Up"];
var idx = 0;
var roomCenter = null;
var roomScale = null;
var currentWall = 0;

var camera;
var faceModel;

function initialize(camera_, faceModel_)
{
    camera = camera_;
    faceModel = faceModel_;
}

function preComputeCenters()
{
    computedCenters = [];
    if (roomCenter && roomScale)
    {
        var factor = 1;
        computedCenters[0] = Qt.vector3d(roomCenter.x, roomCenter.y, roomCenter.z - (roomScale.z * factor));
        computedCenters[1] = Qt.vector3d(roomCenter.x, roomCenter.y, roomCenter.z + (roomScale.z * factor));
        computedCenters[2] = Qt.vector3d(roomCenter.x  + (roomScale.x * factor), roomCenter.y, roomCenter.z);
        computedCenters[3] = Qt.vector3d(roomCenter.x  - (roomScale.x * factor), roomCenter.y, roomCenter.z);
        computedCenters[4] = Qt.vector3d(roomCenter.x, roomCenter.y  + (roomScale.y * factor), roomCenter.z);
        computedCenters[5] = Qt.vector3d(roomCenter.x, roomCenter.y  - (roomScale.y * factor), roomCenter.z);
    }
}

function preComputeWalls()
{
    walls = [];
    if (roomCenter && roomScale)
    {
        walls[0] = Qt.vector3d(roomCenter.x, roomCenter.y, roomCenter.z + roomScale.z);
        walls[1] = Qt.vector3d(roomCenter.x, roomCenter.y, roomCenter.z - roomScale.z);
        walls[2] = Qt.vector3d(roomCenter.x - roomScale.x, roomCenter.y, roomCenter.z);
        walls[3] = Qt.vector3d(roomCenter.x + roomScale.x, roomCenter.y, roomCenter.z);
        walls[4] = Qt.vector3d(roomCenter.x, roomCenter.y - roomScale.y, roomCenter.z);
        walls[5] = Qt.vector3d(roomCenter.x, roomCenter.y + roomScale.y, roomCenter.z);
    }
}

function moveCameraToWall(wallIdx)
{
    currentWall = wallIdx;
    var upVec = Qt.vector3d(0, 1, 0);
    if (wallIdx > 3)
        upVec = Qt.vector3d(0, 0, 1);

    camera.upVector = upVec;
    camera.setCameraCenter(walls[currentWall])
    camera.setCameraEye(computedCenters[currentWall])
}

function generateWallFacesModel()
{
    if (faceModel)
    {
        faceModel.clear();
        for (var i in walls)
            faceModel.append({ "name" : facesNames[i] , "idx" : i});
    }
}

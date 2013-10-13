.pragma library


// THERE ARE 6 WALLS WHICH WHICH BE SAVED IN THE FOLLOWING ORDER
// NORTH, SOUTH, EAST, WEST, UP, DOWN

var walls = null;
var computedEyes = null;
var facesNames = ["North", "South", "East", "West", "Down", "Up"];
var facesComputeVectors = [Qt.vector3d(0, 0, -1), Qt.vector3d(0, 0, 1), Qt.vector3d(1, 0, 0), Qt.vector3d(-1, 0, 0), Qt.vector3d(0, -1, 0), Qt.vector3d(0, 1, 0)]
var facesRotateVectors = [Qt.vector3d(0, -1, 0), Qt.vector3d(0, -1, 0), Qt.vector3d(0, -1, 0), Qt.vector3d(0, 1, 0), Qt.vector3d(0, 0, 1), Qt.vector3d(0, 0, -1)]
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

function zoomOnWall(zoomFactor, wallIdx)
{
    camera.setCameraEye(Qt.vector3d(roomCenter.x + (facesComputeVectors[wallIdx].x * roomScale.x * zoomFactor),
                                    roomCenter.y + (facesComputeVectors[wallIdx].y * roomScale.y * zoomFactor),
                                    roomCenter.z + (facesComputeVectors[wallIdx].z * roomScale.z * zoomFactor)));
}

function rotateOnWall(rotAngle, wallIdx)
{
    camera.setCameraCenter(rotateCenterPoint(walls[wallIdx], facesRotateVectors[wallIdx], (Math.PI * rotAngle) / 180))
}

function xAxisRotation(point, angle)
{
    return Qt.vector3d(point.x,
                       Math.cos(angle) * point.y - point.z * Math.sin(angle),
                       Math.sin(angle) * point.y + point.z * Math.cos(angle))
}

function yAxisRotation(point, angle)
{
    return Qt.vector3d(Math.sin(angle) * point.z + point.x * Math.cos(angle),
                       point.y,
                       Math.cos(angle) * point.z - point.x * Math.sin(angle))
}

function zAxisRotation(point, angle)
{
    return Qt.vector3d(Math.cos(angle) * point.x - point.y * Math.sin(angle),
                       Math.sin(angle) * point.x + point.y * Math.cos(angle),
                       point.z)
}

function rotateCenterPoint(centerPoint, axis, angle)
{
    if (axis.x !== 0)
        return xAxisRotation(centerPoint, axis.x * angle)
    else if (axis.y !== 0)
        return yAxisRotation(centerPoint, axis.y * angle)
    else
        return zAxisRotation(centerPoint, axis.z * angle);
}

function preComputeEyes(factor)
{
    computedEyes = [];
    if (roomCenter && roomScale)
    {
        if (!factor)
            factor = 1;
        for (var i = 0; i < 6; i++)
            computedEyes[i] = Qt.vector3d(roomCenter.x + (facesComputeVectors[i].x * roomScale.x * factor),
                                          roomCenter.y + (facesComputeVectors[i].y * roomScale.y * factor),
                                          roomCenter.z + (facesComputeVectors[i].z * roomScale.z * factor));
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
        walls[4] = Qt.vector3d(roomCenter.x, roomCenter.y + roomScale.y, roomCenter.z);
        walls[5] = Qt.vector3d(roomCenter.x, roomCenter.y - roomScale.y, roomCenter.z);
    }
}

function moveCameraToWall(wallIdx)
{
    currentWall = wallIdx;
    var upVec = Qt.vector3d(0, 1, 0);
    if (wallIdx > 3)
        upVec = Qt.vector3d(0, 0, 1);

    camera.upVector = upVec;
    console.log(upVec + " " + walls[currentWall] + "");
    camera.setCameraCenter(walls[currentWall])
    camera.setCameraEye(computedEyes[currentWall])
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

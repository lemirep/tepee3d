import QtQuick 2.0
import Qt3D 2.0

Camera  // OPENGL CAMERA
{
    property real angle : 0;
    property real xCam : 0;
    property real yCam : 1;
    property real zCam : 1;
    property real xCamCenter : xCam;
    property real yCamCenter : yCam;
//    property real yCamCenter : 15;
    property real zCamCenter : zCam + 200;
//    property real zCamCenter : 0;


    objectName : "glCamera"
    eye:         Qt.vector3d(xCam, yCam, zCam);
    center :     Qt.vector3d(xCamCenter, yCamCenter, zCamCenter);
    upVector :   Qt.vector3d(0, 1, 0)
    fieldOfView : 60
    farPlane : 1000 // FARTHEST VISIBLE VIEW DISTANCE DEF : 1000
    nearPlane : 1 // NEAREST VISIBLE DISTANCE DEF : 5
    eyeSeparation : 0 // FOR STEREO RENDERING AKA 3D

    Behavior on xCam    {SmoothedAnimation {velocity: 200;}}
    Behavior on yCam    {SmoothedAnimation {velocity : 200;}}
    Behavior on zCam    {SmoothedAnimation {velocity : 200;}}
    Behavior on xCamCenter    {SmoothedAnimation {velocity: 200;}}
    Behavior on yCamCenter    {SmoothedAnimation {velocity : 200;}}
    Behavior on zCamCenter    {SmoothedAnimation {velocity : 200;}}


    function resetCamera()
    {
        xCam = 0;
        yCam = 0;
        zCam = 0;
    }

    function moveTo(x, y, z)
    {
        xCam = x;
        yCam = y;
        zCam = z;
        console.log("x : " + x + " y : " + y + " z : " + z);
        camera_timer.stop();
    }






    // DEFINE CAMERA ANIMATIONS HERE


}

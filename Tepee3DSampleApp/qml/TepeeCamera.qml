import QtQuick 2.0
import Qt3D 2.0

Camera  // OPENGL CAMERA
{
    property real angle : 0;
    property real eyeX : 0;
    property real eyeY : 1;
    property real eyeZ : 1;
    property real centerX : 0;
    property real centerY : 1;
    property real centerZ : -200;


    objectName : "glCamera"
    eye:        Qt.vector3d(eyeX, eyeY, eyeZ)
    center :    Qt.vector3d(centerX, centerY, centerZ)
    upVector :   Qt.vector3d(0, 1, 0)
    fieldOfView : 60
    farPlane : 1000 // FARTHEST VISIBLE VIEW DISTANCE DEF : 1000
    nearPlane : 0.1 // NEAREST VISIBLE DISTANCE DEF : 5
    eyeSeparation : 0 // FOR STEREO RENDERING AKA 3D

    Behavior on eyeX      {SmoothedAnimation {duration : mainWindow.camera_movement_duration}}
    Behavior on eyeY      {SmoothedAnimation {duration : mainWindow.camera_movement_duration}}
    Behavior on eyeZ      {SmoothedAnimation {duration : mainWindow.camera_movement_duration}}
    Behavior on centerX    {SmoothedAnimation {duration : mainWindow.camera_movement_duration}}
    Behavior on centerY    {SmoothedAnimation {duration : mainWindow.camera_movement_duration}}
    Behavior on centerZ    {SmoothedAnimation {duration : mainWindow.camera_movement_duration}}


    function setCameraCenter(centerVector)
    {
        centerX = centerVector.x
        centerY = centerVector.y
        centerZ = centerVector.z
    }

    function setCameraEye(eyeVector)
    {
        eyeX = eyeVector.x
        eyeY = eyeVector.y
        eyeZ = eyeVector.z
    }
}

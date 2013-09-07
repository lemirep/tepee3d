import QtQuick 2.1
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

    eye:        Qt.vector3d(eyeX, eyeY, eyeZ)
    center :    Qt.vector3d(centerX, centerY, centerZ)
    upVector :   Qt.vector3d(0, 1, 0)
    fieldOfView : 58 // 60 FOR 4/3 IS FINE BUT 58 IS NEEDED FOR 16/9
    farPlane : 1000 // FARTHEST VISIBLE VIEW DISTANCE DEF : 1000
    nearPlane : 5 // NEAREST VISIBLE DISTANCE DEF : 5
    eyeSeparation : 0 // FOR STEREO RENDERING AKA 3D
    adjustForAspectRatio : true;

    Behavior on eyeX      {SmoothedAnimation {velocity : mainWindow.camera_movement_velocity}}
    Behavior on eyeY      {SmoothedAnimation {velocity : mainWindow.camera_movement_velocity}}
    Behavior on eyeZ      {SmoothedAnimation {velocity : mainWindow.camera_movement_velocity}}
    Behavior on centerX    {SmoothedAnimation {velocity : mainWindow.camera_movement_velocity}}
    Behavior on centerY    {SmoothedAnimation {velocity : mainWindow.camera_movement_velocity}}
    Behavior on centerZ    {SmoothedAnimation {velocity : mainWindow.camera_movement_velocity}}

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

    function getCameraOrientation()
    {
        var viewVector = computeViewVector();
        var magnitude = computeViewVectorMagnitude();
        return Qt.vector3d(viewVector.x / magnitude, viewVector.y / magnitude, viewVector.z / magnitude)
//        return Qt.vector3d()
    }

    function computeViewVectorMagnitude()
    {
        var viewVector = computeViewVector();
        return Math.sqrt((viewVector.x * viewVector.x) + (viewVector.y * viewVector.y) + (viewVector.z * viewVector.z))
    }

    function computeViewVector()
    {
        // VECTOR FROM EYE TO CENTER
        return Qt.vector3d(center.x - eye.x, center.y - eye.y, center.z - eye.z);
    }
}

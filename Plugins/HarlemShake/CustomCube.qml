import QtQuick 2.1
import Qt3D 2.0
import Qt3D.Shapes 2.0
import QtQuick.Particles 2.0
import QtGraphicalEffects 1.0

Cube
{
    id : customcube

    property string cubeColor;

    property double cubeScaleToStart;
    property double cubeScaleToEnd;
    property int    cubeScaleDuration;
    property int    cubeScalePauseDuration;

    property string cubeColorAnimationStart;
    property string cubeColorAnimationEnd;
    property int    cubeColorAnimationDuration;

    property alias  cubeRotationTarget :rotation_animation.target
    property int    cubeRotationDuration;
    property alias  axisX : xRT;
    property alias  angleX : xRT.angle
    property alias  axisY : yRT;
    property alias  angleY : yRT.angle
    property alias  axisZ : zRT;
    property alias  angleZ : zRT.angle

    property bool globalrunning : false;

    scale : 1
    effect: Effect {id : effect; color: cubeColor}
    transform: [
        Rotation3D {
            id : xRT
            angle: 0
            axis: Qt.vector3d(1, 0, 0)
        },
        Rotation3D {
            id: zRT
            angle: 45.0
            axis: Qt.vector3d(0, 0, 1)
        },
        Rotation3D {
            id : yRT
            angle: 45.0
            axis: Qt.vector3d(0, -1, 0)
        }
    ]
    SequentialAnimation {
        id : color_animation
        running : globalrunning;
        loops : Animation.Infinite
        PropertyAnimation {target:effect; properties: "color"; to: cubeColorAnimationStart; duration: cubeColorAnimationDuration; }
        PropertyAnimation {target:effect; properties: "color"; to: cubeColorAnimationEnd; duration: cubeColorAnimationDuration; }
        PropertyAnimation {target:effect; properties: "color"; to: cubeColor; duration: cubeColorAnimationDuration;}
    }
    SequentialAnimation {
        id : scale_animation
        running : globalrunning;
        loops : Animation.Infinite
        NumberAnimation {target : customcube; property: "scale"; to: cubeScaleToStart; duration : cubeScaleDuration; easing.type: Easing.InOutElastic}
        PauseAnimation { duration: cubeScalePauseDuration}
        NumberAnimation {target : customcube; property: "scale"; to: cubeScaleToEnd; duration : cubeScaleDuration; easing.type: Easing.InOutElastic}
    }
    RotationAnimation {id :rotation_animation; property: "angle"; running : globalrunning; loops : Animation.Infinite; from: 0; to : 360.0; duration: cubeRotationDuration;}
}

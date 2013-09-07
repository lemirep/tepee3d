import QtQuick 2.1
import Qt3D 2.0
import Qt3D.Shapes 2.0

Quad
{
    id : main_wall

    property color wallIndicatorColor : "yellow"
    property string wallIndicatorTexture;

    scale : 1
    position : Qt.vector3d(0, 0, 0)

    Behavior on z {NumberAnimation {duration : 30000}}
    Behavior on y {NumberAnimation {duration : 30000}}
    Behavior on z {NumberAnimation {duration : 30000}}

    function    showFaceIndicator()
    {
        if (!wallIndicatorAnimation.running)
            wallIndicatorAnimation.start()
    }

    SequentialAnimation
    {
        id : wallIndicatorAnimation
        SmoothedAnimation { id : scaleUpAnim; target: faceIndicator; property: "scale"; to : 0.5; velocity: 0.2; duration : -1; easing.type: Easing.InOutQuad }
        SmoothedAnimation { id : scaleDownAnim; target: faceIndicator; property: "scale"; to : 0.05; velocity: 1; duration : -1; easing.type: Easing.InOutQuad }
    }

    Quad
    {
        id : faceIndicator
        scale : 0.05
        enabled : (scale > 0.1)
        position : Qt.vector3d(0, faceIndicatorDistance, 0)
        inheritEvents : true
        effect : Effect {
           texture : wallIndicatorTexture
            blending : true
        }
    }
}

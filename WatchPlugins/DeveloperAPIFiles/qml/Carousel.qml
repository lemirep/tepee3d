import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0


Item3D
{
    property alias radius : carousel_cylinder.radius
    property alias length : carousel_cylinder.length
    property int   nbRows : 2

    property real delegateWidth; // SHOULD BE CALCULATED FROM RADIUS AND nbrRows
    property real delegateHeight;

    mesh: CylinderMesh {
        id : carousel_cylinder
        radius: 0.5
        length: 3.0
        levelOfDetail : 1
    }

    transform : [Rotation3D {axis : Qt.vector3d(1, 0, 0); angle : 90}]

    effect: Effect {
        color: "#aaca00"
    }
}


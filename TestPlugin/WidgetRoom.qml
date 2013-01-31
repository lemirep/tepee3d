// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
/*
Item3D
{
    scale:0.2
    position:Qt.vector3d(0,1.5,6)
    mesh : Mesh {source:"Resources/Models/dog.3ds"}
}
*/

Item3D{
     id: item
     signal qmlSignal()
    Cube
    {
        id : cube_orange
        effect: Effect {color: "orange"}
        scale : 2
        position : Qt.vector3d(0, 0, 0)
        onDoubleClicked  : console.log("pouet1")
    }


    Cube
    {
        id : cube_blue
        effect: Effect {color: "blue"}
        scale : 2
        position : Qt.vector3d(-3, 0, 0)
        onDoubleClicked  : console.log("pouet3")

    }
    Cube
    {


        id : cube_red
        effect: Effect {color: "red"}
        scale : 2
        position : Qt.vector3d(3, 0, 0)
        onClicked:{item.qmlSignal(); console.log("send signal from qml")}
        onDoubleClicked  :item.qmlSignal()
    }
 position: Qt.vector3d(0, 0, 0)
}


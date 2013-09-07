import QtQuick 2.1
import Qt3D 2.0
import Qt3D.Shapes 2.0

Item3D
{
    property string fileName : fileLoader.getFileName();
    property real posAngle : (2 * Math.PI / fileLoader.getMaxCount()) * (fileLoader.getDelegateIndex())
    property real radius : 10

    x : Math.cos(posAngle) * radius
    z : Math.sin(posAngle) * radius
    y : 0 // ELEMENT WILL BE ON FLOOR LEVEL

//    Component.onCompleted:    {console.log("File Completed")}

    Cube
    {
        scale : 2
        onClicked : {fileBrowserItem.setSelected(fileName)}
        onHoverEnter : {effect.color = "green"}
        onHoverLeave : {effect.color = "red"}
        effect : Effect {color : "red"}
    }
}

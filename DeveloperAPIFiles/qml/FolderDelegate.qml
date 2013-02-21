import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0

Item3D
{
    id : folder_delegate_item

    property string folderName : fileLoader.getFileName();
    property real posAngle : (2 * Math.PI / fileLoader.getMaxCount()) * (fileLoader.getDelegateIndex())
    property real radius : 10

    x : Math.cos(posAngle) * radius
    z : Math.sin(posAngle) * radius
    y : 0 // ELEMENT WILL BE ON FLOOR LEVEL

    Component.onCompleted:    {console.log("Folder Completed")}

    Sphere
    {
        scale : 2
        onClicked : {console.log("Click On Folder"); fileBrowserItem.goToFolder(folderName)}
        onHoverEnter : {effect.color = "orange"}
        onHoverLeave : {effect.color = "lightsteelblue"}
        effect : Effect {color : "lightsteelblue"}
    }
}

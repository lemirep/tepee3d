import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import "js/Walls.js" as Walls;

// IN THE LONG TERM THE CUBE WILL BE REPLACED BY A HOME MADE MODEL
// THIS WAY EACH FACE WILL HAVE A ON PRESS METHOD
// AND THE VIEW WILL CHANGE TO THE CORRESPONDING WALL ON THAT PRESS


Item3D
{

    position : room_loader.getPosition()
    property variant widgetModel : room_loader.getWidgetsModel()
    transform : [Scale3D {scale : room_loader.getScale()}]


    function    moveToFace(faceIdx)
    {
        mainWindow.onRoomFaceSwitch();
        mainWindow.currentRoomFaceId = faceIdx;
        Walls.moveCameraToWall(camera, faceIdx);
    }

    Quad
    {
        id : north_wall
        scale : 1
        position : Qt.vector3d(0, 0, 0)
        enabled : (mainWindow.currentRoomFaceId != 1)
        effect : face_effect
        transform : [Rotation3D {angle : 90; axis: Qt.vector3d(1, 0, 0)},
                     Translation3D {translate : Qt.vector3d(0, 0, 0.5)}]
        onClicked :
        {
            console.log("North")
            moveToFace(0)
        }
    }

    Quad
    {
        id : south_wall
        scale : 1
        position : Qt.vector3d(0, 0, 0)
        enabled : (mainWindow.currentRoomFaceId != 0)
        effect : face_effect
        transform : [Rotation3D {angle : 90; axis: Qt.vector3d(1, 0, 0)},
                     Translation3D {translate : Qt.vector3d(0, 0, -0.5)}]
        onClicked :
        {
            console.log("South")
            moveToFace(1)
        }
    }

    Quad
    {
        id : west_wall
        scale : 1
        position : Qt.vector3d(0, 0, 0)
        enabled : (mainWindow.currentRoomFaceId != 2)
        effect : face_effect
        transform : [Rotation3D {angle : 90; axis: Qt.vector3d(0, 0, 1)},
            Translation3D {translate : Qt.vector3d(0.5, 0, 0)}]
        onClicked :
        {
            console.log("West")
            moveToFace(3)
        }
    }

    Quad
    {
        id : east_wall
        scale : 1
        position : Qt.vector3d(0, 0, 0)
        enabled : (mainWindow.currentRoomFaceId != 3)
        effect : face_effect
        transform : [Rotation3D {angle : 90; axis: Qt.vector3d(0, 0, 1)},
            Translation3D {translate : Qt.vector3d(-0.5, 0, 0)}]
        onClicked :
        {
            console.log("East")
            moveToFace(2)
        }
    }

    Quad
    {
        id : up_wall
        scale : 1
        position : Qt.vector3d(0, 0.5, 0)
        enabled : (mainWindow.currentRoomFaceId != 5)
        effect : face_effect
        onClicked :
        {
            console.log("Up")
            moveToFace(4)
        }
    }

    Quad
    {
        id : down_wall
        scale : 1
        position : Qt.vector3d(0, -0.5, 0)
        enabled : (mainWindow.currentRoomFaceId != 4)
        effect : face_effect
        onClicked :
        {
            console.log("Down")
            moveToFace(5)
        }
    }

    Effect
    {
        id : face_effect
        texture : "Resources/Textures/blue_wall.jpg"
        useLighting : true
    }



    Repeater   // REPEATER THAT WILL CONTAIN THE ROOMS WIDGET ELEMENT
    {
        id : widget_repeater
        model : widgetModel
        delegate : widget_component
    }

    Component
    {
        id : widget_component

        Item3D
        {

            //            SequentialAnimation
            //            {
            //                     id : shaking
            //                     running : widget_loader.item.pressed
            //                     NumberAnimation { target: widget_loader.item; property: "x"; to: 1.0; duration: 200}
            //                     NumberAnimation { target: widget_loader.item; property: "y"; to: 1.0; duration: 200}
            //                     NumberAnimation { target: widget_loader.item; property: "x"; to: 0.0; duration: 200}
            //                     NumberAnimation { target: widget_loader.item; property: "y"; to: 0.0; duration: 200}
            //            }

            Loader
            {
                id : widget_loader
                source : "../../plugins_qml/" + model.pluginName + "/" + model.pluginRoomQmlFile
                onProgressChanged:
                {
                    // console.log("source " + source);
                }
                onLoaded:
                {
                    console.log("Plugin Model Loaded");
                }
            }
        }

    }

}

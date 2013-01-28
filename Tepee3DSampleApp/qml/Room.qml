import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import "js/Walls.js" as Walls;

// IN THE LONG TERM THE CUBE WILL BE REPLACED BY A HOME MADE MODEL
// THIS WAY EACH FACE WILL HAVE A ON PRESS METHOD
// AND THE VIEW WILL CHANGE TO THE CORRESPONDING WALL ON THAT PRESS


Item3D
{
    id : room_item

    position : room_loader.getPosition()
    property int currentFaceId : Walls.idx
    property int pluginRoomID   : room_loader.getRoomId();
    property real faceIndicatorDistance : 0.01
    property variant widgetModel : room_loader.getWidgetsModel()
    property vector3d roomScale :  room_loader.getScale()

    function    moveToFace(faceIdx)
    {
        mainWindow.currentRoomFaceId = faceIdx;
    }

    function getRoomPosition()    {return Qt.vector3d(x, y, z)}
    function getRoomScale()    {return Qt.vector3d(roomScale.x, roomScale.y, roomScale.z)}

    Item3D
    {
        transform : [Scale3D {scale : roomScale}]

        Quad
        {
            id : north_wall
            scale : 1
            position : Qt.vector3d(0, 0, 0)
            enabled : (mainWindow.currentRoomFaceId != 1)
            effect : face_effect
            transform : [Rotation3D {angle : 90; axis: Qt.vector3d(1, 0, 0)},
                Translation3D {translate : Qt.vector3d(0, 0, 0.5)}]

            Quad
            {
                scale : 0.5
                position : Qt.vector3d(0, -faceIndicatorDistance, 0)
                inheritEvents : true
                effect : Effect {
                    color : "yellow"
                    blending : true

                }
            }
            onHoverEnter : {console.log("North")}
            onClicked : {mainWindow.currentRoomFaceId = 0}
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

            Quad
            {
                scale : 0.5
                position : Qt.vector3d(0, faceIndicatorDistance, 0)
                inheritEvents : true
                effect : Effect {
                    color : "blue"
                    blending : true

                }
            }
            onHoverEnter :{console.log("South")}
            onClicked : {mainWindow.currentRoomFaceId = 1}
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

            Quad
            {
                scale : 0.5
                position : Qt.vector3d(0, faceIndicatorDistance, 0)
                inheritEvents : true
                effect : Effect {
                    color : "red"
                    blending : true

                }
            }
            onHoverEnter :{console.log("West")}
            onClicked : {mainWindow.currentRoomFaceId = 3}
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

            Quad
            {
                scale : 0.5
                position : Qt.vector3d(0, -faceIndicatorDistance, 0)
                inheritEvents : true
                effect : Effect {
                    color : "orange"
                    blending : true

                }
            }
            onHoverEnter : {console.log("East")}
            onClicked : {mainWindow.currentRoomFaceId = 2}
        }

        Quad
        {
            id : up_wall
            scale : 1
            position : Qt.vector3d(0, 0.5, 0)
            enabled : (mainWindow.currentRoomFaceId != 4)
            effect : face_effect

            Quad
            {
                scale : 0.5
                position : Qt.vector3d(0, -faceIndicatorDistance, 0)
                inheritEvents : true
                effect : Effect {
                    color : "green"
                    blending : true

                }
            }
            onHoverEnter : {console.log("Down")}
            onClicked :{mainWindow.currentRoomFaceId = 4}
        }

        Quad
        {
            id : down_wall
            scale : 1
            position : Qt.vector3d(0, -0.5, 0)
            enabled : (mainWindow.currentRoomFaceId != 5)
            effect : face_effect

            Quad
            {
                scale : 0.5
                position : Qt.vector3d(0, faceIndicatorDistance, 0)
                inheritEvents : true
                effect : Effect {
                    color : "cyan"
                    blending : true
                }
            }

            onHoverEnter : {console.log("Up")}
            onClicked :{mainWindow.currentRoomFaceId = 5}
        }
    }

    Effect
    {
        id : face_effect
        texture : "Resources/Textures/blue_wall.jpg"
//        texture : "Resources/Pictures/panel_bg2.png"
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

        PluginBase
        {
             pluginRoomId: pluginRoomID
             pluginId : model.pluginId
             pluginName : model.pluginName
             roomQmlFile : model.pluginRoomQmlFile
             menuQmlFile : model.pluginMenuQmlFile
        }

    }
}

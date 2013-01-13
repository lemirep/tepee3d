import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0

// IN THE LONG TERM THE CUBE WILL BE REPLACED BY A HOME MADE MODEL
// THIS WAY EACH FACE WILL HAVE A ON PRESS METHOD
// AND THE VIEW WILL CHANGE TO THE CORRESPONDING WALL ON THAT PRESS

Cube
{
    id : room_elem

    property bool bounce : false;
    property variant widgetModel : room_loader.getWidgetsModel()
    property string texturePath : "Resources/Textures/blue_wall.jpg"

    cullFaces : "CullFrontFaces"
    effect : leaveEffect


    Effect
    {
        id : hoverEffect;
        texture : "Resources/Textures/wood.jpg"
        useLighting : true
    }

    Effect
    {
        id : leaveEffect;
        texture : "Resources/Textures/blue_wall.jpg"
        useLighting : true
    }



    position : room_loader.getPosition()
    transform : [Scale3D {scale : room_loader.getScale()}]

    onHoverEnter:
    {
//        effect = hoverEffect;
//        console.log("Room Name = " + room_properties.roomName);
    }

//    onHoverLeave :
//    {
//        effect = leaveEffect;
//       // texturePath = "Resources/Textures/blue_wall.jpg"
//    }

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


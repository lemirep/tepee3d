import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0

Cube
{
    cullFaces : "CullFrontFaces"
    id : room_elem

    property bool bounce : false;
    property variant widgetModel : null
//    objectName : "RoomInner"



    effect : Effect {
        texture : "Resources/Textures/blue_wall.jpg"
        useLighting : true
    }

    position : room_loader.getPosition()
    transform : [Scale3D {scale : room_loader.getScale()}]


//    Repeater        // REPEATER THAT WILL CONTAIN THE ROOMS WIDGET ELEMENT
//    {
//        id : widget_repeater
//        model : widgetModel
//    }

//    Component
//    {
//        id : widget_component
//        Loader
//        {
//            id : widget_loader
//            source : model.pluginRoomQmlFile
//            onLoaded:
//            {
//                console.log("Plugin Model Loaded");
//            }
//        }
//    }
}


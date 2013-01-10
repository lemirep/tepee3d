import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0

Cube
{
    id : room_elem

//    property int roomId : room_loader.getRoomId();
    property bool bounce : false;
    property variant widgetModel : room_loader.getWidgetsModel()
    property string texturePath : "Resources/Textures/blue_wall.jpg"

    cullFaces : "CullFrontFaces"

    effect : Effect {
        texture : texturePath
        useLighting : true
    }


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
//    scale : 10
    transform : [Scale3D {scale : room_loader.getScale()}]

    onHoverEnter:
    {
        effect = hoverEffect;
    }

    onHoverLeave :
    {
        effect = leaveEffect;
       // texturePath = "Resources/Textures/blue_wall.jpg"
    }

    ListView     // REPEATER THAT WILL CONTAIN THE ROOMS WIDGET ELEMENT
    {
        id : widget_repeater
        model : widgetModel
        delegate : widget_component
        //        onModelChanged :
        //        {
        //            console.log("Model Changed");
        //            if (!model)
        //                console.log("Model is null");
        //        }
        //        onItemAdded :
        //        {
        //            console.log("Item added at " + index)
        //        }
        //        onItemRemoved :
        //        {
        //            console.log("Item removed at " + index)
        //            if (item)
        //            {
        //                console.log("Destroying Item >>>>>>>>>>")
        //                item.enabled = false;
        //            }
        //        }
    }

    Component
    {
        id : widget_component

        //        Cube
        //        {
        //            property real zRot : 0;
        //            property real yRot : 0;

        //            scale : 0.3
        //            position : Qt.vector3d(0, 0, 0)
        //            effect: Effect {color : "red"}
        //        }

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


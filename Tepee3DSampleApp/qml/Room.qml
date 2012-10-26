import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0

//Item3D
//{
Cube
{
    cullFaces : "CullFrontFaces"
    id : room_elem

    property bool bounce : false;

    effect : Effect {
        texture : "Resources/Textures/blue_wall.jpg"
        //            color : "blue"
        //            decal : true
        useLighting : true
        //            material : Material {
        //                ambientColor : "blue";
        //                diffuseColor : "blue"
        //                specularColor : "blue"
        //                shininess : 0.5
        //                emittedLight : "#22000033"
        //            }
    }



    Repeater        // REPEATER THAT WILL CONTAIN THE ROOMS WIDGET ELEMENT
    {
        id : widget_repeater
    }

    //        onClicked :
    //        {
    //            console.log("clicked");
    //            myanim.running = true;
    ////            room_elem.bounce = true
    //            //                console.log("Room Clicked " + room.x + " " + room.y  + " " + room.z);
    //            //        camera.moveTo(x, y, z - scale);
    //        }
}

//    SequentialAnimation on y
//    {
//        id : myanim
//        NumberAnimation { to : 5; duration: 300; easing.type:"OutQuad" }
//        NumberAnimation { to : 0; duration: 300; easing.type:"OutBounce" }
//    }


//}

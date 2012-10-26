// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 2.0
// FOR QTQUICK 3D
import Qt3D 2.0
// FOR QTQUICK 3D SHAPES
import Qt3D.Shapes 2.0

Item
{
    property color cubeColor : "red";
    property real cubeAngle : 0.0;
    property real xpos : 0;
    property real ypos : 0;
    property real zpos : 0;
    property real xrot : 0;
    property real yrot : 0;


    function degToRad(angle)
    {
        return (angle / 180 * 3.141592654);
    }

    anchors.fill: parent
    focus : true

    //    Keys.onLeftPressed:
    //    {
    //        xpos += 0.2;
    //        //        camera.viewAngle -= 0.5;
    //    }
    //    Keys.onRightPressed:
    //    {
    //        xpos -= 0.2;
    //        //        camera.viewAngle += 0.5
    //    }
    //    Keys.onUpPressed:
    //    {
    //        zpos += 0.2;
    //    }
    //    Keys.onDownPressed:
    //    {
    //        zpos -= 0.2;
    //    }
    //    Keys.onPressed:
    //    {
    //        if (event.key == Qt.Key_B)
    //            ypos += 0.2;
    //        else if (event.key == Qt.Key_V)
    //            ypos -= 0.2;
    //    }



    Keys.onLeftPressed:
    {
        yrot -= 1;
        if (yrot < -360)
            yrot += 360;
        console.log("Yrot " + yrot + " Xrot " + xrot);
    }
    Keys.onRightPressed:
    {
        yrot += 1;
        if (yrot > 360)
            yrot -= 360;
        console.log("Yrot " + yrot + " Xrot " + xrot);
    }
    Keys.onUpPressed:
    {
       xrot -= 1;
        if (xrot < -360)
            xrot += 360;
        console.log("Yrot " + yrot + " Xrot " + xrot);
    }
    Keys.onDownPressed:
    {
      xrot += 1;
        if (xrot > 360)
            xrot -= 360;
        console.log("Yrot " + yrot + " Xrot " + xrot);
    }
    Keys.onPressed:
    {
//        if (event.key == Qt.Key_B)
//            ypos += 0.2;
//        else if (event.key == Qt.Key_V)
//            ypos -= 0.2;

        if (event.key == Qt.Key_W)
        {
            var xrad = degToRad(xrot);
            var yrad = degToRad(yrot);
            xpos += Math.sin(yrad);
            ypos -= Math.cos(xrad);
            zpos -= Math.cos(yrad);
        }
        else if (event.key == Qt.Key_S)
        {
            var xrad = degToRad(xrot);
            var yrad = degToRad(yrot);
            xpos -= Math.sin(yrad);
            ypos += Math.cos(xrad);
            zpos += Math.cos(yrad);
        }
    }



    Keys.onSpacePressed:
    {
        console.log("xpos : " + xpos + " ypos : " + ypos + " zpos : " + zpos);
    }

    Viewport
    {
        id : viewportElem
        anchors.fill: parent
        // TO ALLOW SELECTION OF 3D ITEMS
        picking : true
        blending : true
        showPicking : true
        objectName : "viewport"

        //               y ^  _
        //                 |  /| z
        //                 | /
        //                 |/
        //      x <--------/---------
        //                /|
        //               / |
        //              /  |
        //

        light : Light        {
            ambientColor : "#ffffff"
            position : Qt.vector3d(0, 0, 10);
            spotAngle : 180
            spotDirection : Qt.vector3d(0, 0, 10)
            spotExponent : 30
        }

        camera: Camera {
            id : camera
            objectName : "glCamera"
//            eye:         Qt.vector3d(xpos, ypos, zpos);
            eye:         Qt.vector3d(0, 0, 0);
            //            center :     Qt.vector3d(xpos, ypos -0.5, (zpos  + 4));
//            center :     Qt.vector3d(xpos, 1.0, 1000.0);
            center :     Qt.vector3d(0, 1.0, 1000.0);
            upVector :   Qt.vector3d(0, 1, 0)
            fieldOfView : 60 //POS
            farPlane : 2000 // FARTHEST VISIBLE VIEW DISTANCE DEF : 1000
            nearPlane : 0 // NEAREST VISIBLE DISTANCE DEF : 5


        }

        Item3D
        {
            objectName: "root3dObject"
            scale:1
            position : Qt.vector3d(0, 0, 5)
            //    position:Qt.vector3d(0,1.5,6)

            Cube
            {
                scale : 1

                onClicked :
                {
                    console.log("ROOM CLICKED");
                    //                    controller.createNewRoom("room", 1, 1, 1);
                }
            }


            //            mesh : Mesh {source:"Resources/Models/dog.3ds"}

        }

        //        Room
        //        {
        //            position : Qt.vector3d(0, 0, 5)
        //            objectName: "root3dObject"
        //        }


        function    updateCamera()
        {
            var x = xpos;
            var y = ypos;
            var z = zpos;
            var ax = degToRad(xrot);
            var ay = degToRad(yrot);

            camera.eye = Qt.vector3d(Math.cos(ay) * x, Math.sin(ax) * y, z);
            camera.center = Qt.vector3d(Math.cos(ay) *x, 1.0, 1000.0);
        }

        Timer
        {
            id : camera_timer
            running : true
            repeat : true
            interval : 1000 / 24
            onTriggered:
            {
                viewportElem.updateCamera();
            }
            Component.onCompleted:
            {
                camera_timer.start();
            }
        }


    }
}

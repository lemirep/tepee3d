// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 2.0
import Qt3D.Shapes 2.0
import Qt3D 2.0
import BufferedTextureSourcePlugin 1.0

Viewport
{
    id : mainWindow

    property color menu_background_color : "#0066ff";
    property color room_list_component_color : "#0099dd";
    property color room_list_selected_component_color : "#0066cc";
    property color plugin_list_component_color : "#0099dd";
    property color plugin_list_selected_component_color : "#0066cc";
    property real  menu_opacity_deployed : 1.0;
    property int   camera_movement_duration : 500;
    property int   currentRoomId : 0;
    property int   currentRoomFaceId : 0; // NORTH FACE BY DEFAULT, USE FOR CULLING

    width: 1024
    height: 768
    focus : true
    navigation : false
    picking : true      // TO ALLOW MOUSE EVENTS ON 3D ITEMS
    blending : true     // ALLOW TRANSPARENCY
    //    showPicking : true  // FOR DEBUG PURPOSES ONLY
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

    function    onRoomSwitch()
    {
        camera_movement_duration = 1000;
        currentRoomFaceId = 0;
    }

    function    onRoomFaceSwitch()
    {
        camera_movement_duration = 5000;
    }


    lightModel : LightModel {
        //        model : "TwoSided"
        model : "OneSided"
        viewerPosition : "LocalViewer"
        //        viewerPosition : "ViewerAtInfinity"
        ambientSceneColor : "#ffffff"
    }

    light : Light {
        ambientColor : "white";
        diffuseColor : "white"
        specularColor : "white"
        position : Qt.vector3d(10, 10, 100)
        linearAttenuation : 0
    }

    camera: TepeeCamera     {
        id : camera
    }

    Timer
    {
        id : camera_timer
        running : true
        interval : 40
        repeat : true
        onTriggered:
        {
            camera.angle += 0.05
            if (camera.angle >= 360)
                camera.angle -= 360;
            camera.setCameraEye(Qt.vector3d(100 * Math.cos(camera.angle), camera.eyeY, 100 * Math.sin(camera.angle)));
        }
    }



    Keys.onLeftPressed:
    {

    }
    Keys.onRightPressed:
    {
    }
    Keys.onUpPressed:
    {
        camera.zCam += 1;
        //        camera.zCamCenter += 5
        console.log("Eye " + camera.eye.x + "," + camera.eye.y + "," + camera.eye.z + " Center " + camera.center.x + "," + camera.center.y + "," + camera.center.z);
    }
    Keys.onDownPressed:
    {
        camera.zCam -= 1;
    }

    Skybox
    {
        source : "sky15"
    }

    RoomsContainer
    {
        id : roomContainer
    }

//    BufferedTextureSource
//    {
//        sourceItem : menu_center

//    }

    MenuCenter
    {
        id : menu_center
        anchors.fill : parent
    }
}

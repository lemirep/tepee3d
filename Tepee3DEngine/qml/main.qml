//// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 2.1
import Qt3D 2.0
import Qt3D.Shapes 2.0
import QtQuick.Window 2.1
import "js/RoomManagement.js" as RoomManagement
import "js/Walls.js" as Walls
import "js/CameraManagement.js" as CameraManagement
import QtQuick.Particles 2.0

Viewport
{
    id : mainWindow

    property color menu_background_color : "#404040";
    property color room_list_component_color : "#0099dd";
    property color room_list_selected_component_color : "#0066cc";
    property color plugin_list_component_color : "#0099dd";
    property color plugin_list_selected_component_color : "#0066cc";
    property real  menu_opacity_deployed : 1.0;
    property real  menu_opacity_retracted : 0;
    property real  cameraZoom : 1
    property real  cameraRotation : 0
    property int   camera_movement_velocity : 250;
    property int   menuMinimumWidth : 40
    property int   currentRoomId : -1;
    property int   currentRoomFaceId : 0;
    property bool  isAPluginFocused : false;

    property real   defaultFontSize : 14
    property real   smallFontSize : 12
    property real   largeFontSize : 16

    property alias pluginMenuSource : menu_center.pluginMenuSource
    property variant mouseObjectGrabber : null

    signal roomChanged(int roomId);
    signal roomFaceIdChanged(int roomFaceId);

    //    function moveCameraToSkyView()           {CameraManagement.moveCamera(camera, Qt.vector3d(0, 300 + (150 * Math.floor(roomModel.count/ 10)), -200), Qt.vector3d(0, 1, 1), Qt.vector3d(0, 0, 1))}
    function moveCameraToSkyView()           {CameraManagement.moveCamera(camera, Qt.vector3d(0, 100, -200), Qt.vector3d(0, 1, 1), Qt.vector3d(0, 1, 0))}
    function getcurrentIdRoom()              {roomChanged(currentRoomId); return currentRoomId}
    function moveCameraHomeRoom()            {Walls.moveCameraToWall(0)}
    function inRoom()                        {if(currentRoomId <= 0) return false;return true}
    function onRoomSwitch()                  {camera_movement_velocity = 200;currentRoomFaceId = 0;}
    function onRoomFaceSwitch()              {camera_movement_velocity = 100;}
    function postNotification(message)       {notification.sendMessage(message)}


    Component.onCompleted:
    {
        RoomManagement.initialize(camera, roomModel, currentRoomFacesModel);
        moveCameraToSkyView();
        pluginMenuSource = "./Menus/SkyboxPicker.qml"
    }

    onCameraZoomChanged:
    {
        if (inRoom() && !isAPluginFocused)
        {
            Walls.zoomOnWall(cameraZoom, currentRoomFaceId)
        }
    }

    onCameraRotationChanged:
    {
        if (inRoom() && !isAPluginFocused)
        {
            Walls.rotateOnWall(cameraRotation, currentRoomFaceId)
        }
    }

    onCurrentRoomIdChanged:
    {
        console.log("Room Changed " + currentRoomId)
        roomManager.setCurrentRoom(currentRoomId);
        var room = RoomManagement.findRoomInModel(currentRoomId);
        if (room)
        {
            RoomManagement.moveToRoom(room)
            light.position = room.roomPosition;
        }
        else
        {
            light.position = Qt.vector3d(0, 0, 0);
            pluginMenuSource = "./Menus/SkyboxPicker.qml"
        }
        roomChanged(currentRoomId)
        currentRoomFaceId = 0;
    }

    onCurrentRoomFaceIdChanged:
    {
        console.log("ROOM FACE CHANGED >>>>>>>>>>>>" + currentRoomFaceId)
        Walls.moveCameraToWall(currentRoomFaceId)
        roomFaceIdChanged(currentRoomFaceId)
        // UNSET FOCUS STATE OF PLUGINS
        roomManager.unsetFocusPluginsFromRoom();
        cameraZoom = 1;
        cameraRotation = 0;
    } // NORTH FACE BY DEFAULT, USE FOR CULLING


    width : (DEBUG) ? 1280 : Screen.width
    height : (DEBUG) ? 800 : Screen.height

    //    width : Screen.width
    //    height : Screen.height

    navigation : false
    picking : true     // TO ALLOW MOUSE EVENTS ON 3D ITEMS
    blending : true     // ALLOW TRANSPARENCY
    showPicking : false  // FOR DEBUG PURPOSES ONLY
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

    ListModel    {id : currentRoomFacesModel} // STORES FACES INFORMATION ABOUT THE CURRENT ROOM

    lightModel : LightModel {
        //        model : "OneSided"
        //        viewerPosition : "LocalViewer"
        model : "TwoSided"
        viewerPosition : "ViewerAtInfinity"
        ambientSceneColor : "#ffffff"
    }

    light : Light {
        id : light
        ambientColor : "white";
        diffuseColor : "white"
        specularColor : "white"
        position : Qt.vector3d(0, 0, 0)
        linearAttenuation : 0
        Behavior on position.x {SmoothedAnimation {velocity : 100; duration : -1}}
        Behavior on position.y {SmoothedAnimation {velocity : 100; duration : -1}}
        Behavior on position.z {SmoothedAnimation {velocity : 100; duration : -1}}
    }

    camera: TepeeCamera     {id : camera}

    //    Keys.onLeftPressed:    {}
    //    Keys.onRightPressed:    {}
    //    Keys.onUpPressed:    {}
    //    Keys.onDownPressed:    {}

    Skybox            {source : "Resources/Textures/skyboxes/" + ((roomManager.skyboxPath == "") ? "bridge" : roomManager.skyboxPath)}
    RoomsContainer    {id : roomContainer}
    NotificationManager    {id : notification}
    MenuCenter        {id : menu_center; anchors.fill : parent}
    FpsCounter {}

//    ParticleSystem
//    {
//        id : tepee3d_particle_system
//        ImageParticle
//        {
//            source: "Resources/Pictures/smoke.png"
//            color: "dodgerblue"
//            alpha: 0.9
//            opacity: 0.5
//            rotationVariation: 180
//            groups: ["tepee3d_particles"]
//        }
//        ItemParticle
//        {
//            delegate : Component {
//                Rectangle
//                {
//                    width : 10
//                    height : 10
//                    color : "lawngreen"
//                }
//            }
//            groups: ["tepee3d_particles_click"]
//        }
//        ImageParticle
//        {
//            source: "Resources/Pictures/smoke.png"
//            color: "chartreuse"
//            alpha: 0.9
//            opacity: 0.5
//            rotationVariation: 180
//            groups: ["tepee3d_particles_click"]
//        }
//    }

//    Emitter
//    {
//        id : tepee3d_particle_emitter
//        height: 50
//        width: height
//        shape : EllipseShape
//        size: 30
//        sizeVariation: 30
//        lifeSpan: 2000
//        lifeSpanVariation: 1000
//        system: tepee3d_particle_system
//        emitRate: 20
//        group : "tepee3d_particles"
//        acceleration: AngleDirection{angle: 30}
//        velocity: PointDirection{xVariation: 50; yVariation: 50}
//        enabled : true
//    }
//    Emitter
//    {
//        id : tepee3d_particle_click_emitter
//        height: 50
//        width: height
//        shape : EllipseShape
//        size: 30
//        //        sizeVariation: 5
//        lifeSpan: 1000
//        //        lifeSpanVariation: 500
//        system: tepee3d_particle_system
//        group : "tepee3d_particles_click"
//        acceleration: AngleDirection{angle: 0}
//        velocity: PointDirection{xVariation: 70; yVariation: 70}
//        enabled : false
//    }
}

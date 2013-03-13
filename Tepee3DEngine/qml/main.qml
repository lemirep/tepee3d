// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import BufferedTextureSourcePlugin 1.0

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
    property int   camera_movement_velocity : 250;
    property int   menuMinimumWidth : 40
    property int   currentRoomId : -1;
    property int   currentRoomFaceId : 0;

    property alias pluginMenuSource : menu_center.pluginMenuSource
    property variant mouseObjectGrabber : null

    signal roomChanged(int roomId);
    signal roomFaceIdChanged(int roomFaceId);

    function moveCameraToSkyView()           {CameraManagement.moveCamera(camera, Qt.vector3d(0, 300 + (150 * Math.floor(roomModel.count/ 10)), -200), Qt.vector3d(0, 1, 1), Qt.vector3d(0, 0, 1))}
    function getcurrentIdRoom()              {roomChanged(currentRoomId); return currentRoomId}
    function moveCameraHomeRoom()            {Walls.moveCameraToWall(0)}
    function inRoom()                        {if(currentRoomId <= 0) return false;return true}
    function onRoomSwitch()                  {camera_movement_velocity = 200;currentRoomFaceId = 0;}
    function onRoomFaceSwitch()              {camera_movement_velocity = 100;}
    function postNotification(message)       {notification.sendMessage(message)}

    Component.onCompleted:    {RoomManagement.initialize(camera, roomModel, currentRoomFacesModel); moveCameraToSkyView()}

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
            light.position = Qt.vector3d(0, 0, 0);
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
    } // NORTH FACE BY DEFAULT, USE FOR CULLING


    // FOR 16 / 9
    width: 1280
    height: 720

    //    width: 1680
    //    height: 1050
    // FOR 4 / 3
    //    width : 1024
    //    height : 728
    //    focus : true
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

    Skybox            {source : "sky15"}
    RoomsContainer    {id : roomContainer}
    MenuCenter        {id : menu_center; anchors.fill : parent}
    //    BufferedTextureSource    {sourceItem : menu_center}
    NotificationManager    {id : notification}
    FpsCounter {}
}

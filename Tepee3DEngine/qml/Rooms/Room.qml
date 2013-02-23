import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import View 1.0

// IN THE LONG TERM THE CUBE WILL BE REPLACED BY A HOME MADE MODEL
// THIS WAY EACH FACE WILL HAVE A ON PRESS METHOD
// AND THE VIEW WILL CHANGE TO THE CORRESPONDING WALL ON THAT PRESS


Item3D
{
    id : room_item

    position : room_loader_item.roomPosition;
    property int roomId   : room_loader_item.roomId;
    property bool isCurrentRoom : (roomId === mainWindow.currentRoomId)
    property int currentFaceId : mainWindow.currentRoomFaceId;
    property real faceIndicatorDistance : 0.01
    property variant widgetModel : room_loader_item.widgetsModel
    property vector3d roomScale :  room_loader_item.roomScale

    function getRoomPosition()    {return Qt.vector3d(x, y, z)}
    function getRoomScale()    {return Qt.vector3d(roomScale.x, roomScale.y, roomScale.z)}

    function moveToFace(faceIdx)
    {
        if (mainWindow.currentRoomId === -1)
            mainWindow.currentRoomId = roomId;
        if (isCurrentRoom)
            mainWindow.currentRoomFaceId = faceIdx;
    }

    function showWallsIndicator()
    {
        northWall.showFaceIndicator();
        southWall.showFaceIndicator();
        eastWall.showFaceIndicator();
        westWall.showFaceIndicator();
        upWall.showFaceIndicator();
        downWall.showFaceIndicator();
    }

    onCurrentFaceIdChanged:    {if (isCurrentRoom) showWallsIndicator()}
    onIsCurrentRoomChanged:    {if (isCurrentRoom) showWallsIndicator()}

    Item3D
    {
        transform : [Scale3D {scale : roomScale}]


        //        QmlAsTexture
        //        {
        //            sourceItem: qml_texture
        //            effectItem: face_effect
        //        }

        //        ShaderEffectSource
        //        {
        //            id : qml_texture
        //            width : 128
        //            height : 128
        //            recursive : false
        //            mipmap : false
        //            hideSource: true
        //            sourceItem: Rectangle {
        //                width : 512
        //                height : 512
        //                color : "orange"
        //            }
        ////            live : true
        //        }

        //        Rectangle
        //        {
        //            color : "orange"
        //            x : mainWindow.width / 2
        //            y : mainWindow.height / 3
        //            width : 50
        //            height : 50
        //        }

        states : [
            State
            {
                name : "wallDown"
                PropertyChanges {target: northWall; z : 100}
                PropertyChanges {target: southWall; z : -100}
                PropertyChanges {target: eastWall;  z : -100}
                PropertyChanges {target: westWall;  z : 100}
                PropertyChanges {target: upWall;    y : 100}
                PropertyChanges {target: downWall;  y : -100}
                //                when : isCurrentRoom
            }]

        RoomWall
        {
            id : northWall
            wallIndicatorColor: "yellow"
            wallIndicatorTexture: "../Resources/Textures/wall_indicator_north.png"
            rotationAngle:  -90
            rotationAxis: Qt.vector3d(1, 0, 0)
            panelRotationAxis: Qt.vector3d(0, 1, 0)
            panelRotationAngle: 180
            translationVector: Qt.vector3d(0, 0, 0.5)
            enabled : (!isCurrentRoom || currentFaceId != 1)
            effect : face_effect
            //            onHoverEnter : {console.log("North")}
            onClicked : {moveToFace(0)}
        }

        RoomWall
        {
            id : southWall
            wallIndicatorColor: "blue"
            wallIndicatorTexture: "../Resources/Textures/wall_indicator_south.png"
            rotationAngle:  90
            rotationAxis: Qt.vector3d(1, 0, 0)
            translationVector: Qt.vector3d(0, 0, -0.5)
            enabled : (!isCurrentRoom || currentFaceId != 0)
            effect : face_effect
            //            onHoverEnter : {console.log("South")}
            onClicked : {moveToFace(1)}
        }

        RoomWall
        {
            id : westWall
            wallIndicatorColor: "red"
            wallIndicatorTexture: "../Resources/Textures/wall_indicator_west.png"
            rotationAngle:  90
            rotationAxis: Qt.vector3d(0, 0, 1)
            panelRotationAxis: Qt.vector3d(0, 1, 0)
            panelRotationAngle: -90
            translationVector: Qt.vector3d(0.5, 0, 0)
            enabled : (!isCurrentRoom || currentFaceId != 2)
            effect : face_effect
            //            onHoverEnter : {console.log("West")}
            onClicked : {moveToFace(3)}
        }

        RoomWall
        {
            id : eastWall
            wallIndicatorColor: "orange"
            wallIndicatorTexture: "../Resources/Textures/wall_indicator_east.png"
            rotationAngle:  -90
            rotationAxis: Qt.vector3d(0, 0, 1)
            panelRotationAxis: Qt.vector3d(0, 1, 0)
            panelRotationAngle: 90
            translationVector: Qt.vector3d(-0.5, 0, 0)
            enabled : (!isCurrentRoom || currentFaceId != 3)
            effect : face_effect
            //            onHoverEnter : {console.log("East")}
            onClicked : {moveToFace(2)}
        }

        RoomWall
        {
            id : upWall
            wallIndicatorColor: "green"
            wallIndicatorTexture: "../Resources/Textures/wall_indicator_up.png"
            rotationAngle:  180
            rotationAxis: Qt.vector3d(0, 0, 1)
            translationVector: Qt.vector3d(0, 0.5, 0)
            panelRotationAxis: Qt.vector3d(0, 1, 0)
            panelRotationAngle: 180
            enabled : (!isCurrentRoom || currentFaceId != 4)
            effect : face_effect
            //            onHoverEnter : {console.log("Up")}
            onClicked : {moveToFace(4)}
        }

        RoomWall
        {
            id : downWall
            wallIndicatorColor: "cyan"
            wallIndicatorTexture: "../Resources/Textures/wall_indicator_down.png"
            rotationAngle:  0
            rotationAxis: Qt.vector3d(0, 0, 1)
            panelRotationAxis: Qt.vector3d(0, 1, 0)
            panelRotationAngle: 180
            translationVector: Qt.vector3d(0, -0.5, 0)
            enabled : (!isCurrentRoom || currentFaceId != 5)
            effect : face_effect
            //            onHoverEnter : {console.log("Down")}
            onClicked : {moveToFace(5)}
        }
    }

    Effect
    {
        id : face_effect
        texture : "../Resources/Textures/blue_wall.jpg"
        //        dynamicTexture : qml_texture
        //        texture : "Resources/Pictures/panel_bg2.png"
        useLighting : true

        onEffectChanged :
        {
            console.log("Effect Changed");
        }
    }

    Repeater   // REPEATER THAT WILL CONTAIN THE ROOMS WIDGET ELEMENT
    {
        id : widget_repeater
        model : widgetModel
        delegate : widget_component
    }

    FileExplorer    {    }

    Component
    {
        id : widget_component

        PluginBase
        {
            pluginRoomId: roomId
            pluginId : model.pluginId
            pluginName : model.pluginName
            roomQmlFile : model.pluginRoomQmlFile
            menuQmlFile : model.pluginMenuQmlFile
        }

    }
}

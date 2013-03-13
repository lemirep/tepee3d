// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import QtQuick.Particles 2.0
import "js/script.js" as Script
import "js/pocket.js" as Pocket
import "js/twitter.js" as Twitter
import "js/storage.js" as Storage
import "js/translate.js" as AzureTranslate

Item3D
{
    id : testplugin_container

    property real zRot : 1;
    property real yRot : 0;
    property color col : "red"
    position : Qt.vector3d(-10, 0, 0)

    // HAS TO BE IMPLEMENTED TO HANDLE STATE CHANGE
    // USE FOR LOGIC CHANGE, FOR ANIMATION USE RATHER STATES
    function focusStateChanged(focusStateValue)
    {
        console.log("<<<<<<<<<<<<<<<<<<<<<FocusStateChanged " + focusStateValue);
        //Script.requestToken();
        Script.getTwitterTimeAndLogin();
        console.log("<<<------------------<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");

        switch (focusStateValue)
        {
        case 0:
            switchToIdleFocusView();
            break;
        case 1:
            switchToSelectedFocusView();
            break;
        case 2:
            switchToFocusedView();
            break;
        default:
            break;
        }
    }

    // HAS TO BE IMPLEMENTED
    function roomEntered()    {}
    // HAS TO BE IMPLEMENTED
    function roomLeft()    {}

    function switchToIdleFocusView()    {plugin_base.moveCamera()}
    function switchToSelectedFocusView()    {}
    function switchToFocusedView()
    {
        //        var eye = camera.eye;
        var eye = plugin_base.getRoomPosition();
        var center = plugin_base.getRoomPosition();
        eye.z += (-10)
        center.x += testplugin_container.x
        center.y += testplugin_container.y
        center.z += testplugin_container.z
        plugin_base.moveCamera(eye, center);
    }

    function setColorAssign(msg) {
        console.log("SET COLOR From DB  :  " + msg);
        cube_plugin.effect.color = msg;
        col = msg;
    }

    states : [
        State {
            name : "idle"
            PropertyChanges {target: testplugin_container; col : apc.getColor()}
            when : plugin_base.getFocusState() === 0
        },
        State {
            name : "selected"
            PropertyChanges {target: testplugin_container; col : apc.getColor()}
            when : plugin_base.getFocusState() === 1
        },
        State {
            name : "focused"
            PropertyChanges {target: testplugin_container; col : apc.getColor()}
            when : plugin_base.getFocusState() === 2
        }
    ]

    Item3D
    {
        id : buttons
        enabled : true
        Cube
        {
            id : cube_orange
            effect: Effect {color: "orange"}
            scale : 1
            position : Qt.vector3d(-1, 1, -2)
            onClicked:{apc.selectColor("orange");cube_plugin.effect.color = "orange";}
        }

        Cube
        {
            id : cube_red
            effect: Effect {color: "red"}
            scale : 1
            position : Qt.vector3d(2, 1, 1)
            onClicked:{apc.selectColor("red");cube_plugin.effect.color = "red";}
        }

        Cube
        {
            id : cube_blue
            effect: Effect {color: "blue"}
            scale : 1
            position : Qt.vector3d(-2, 1, 0)
            onClicked:{apc.selectColor("blue");cube_plugin.effect.color = "blue";}
        }
    }

    Item3D
    {
        id : cube_plugin
        mesh: Mesh { source: "./Batman.obj" }
        scale : 0.03
        position : Qt.vector3d(0, -5, 0)

        effect: Effect {color :apc.getColor(); useLighting : true}

        onClicked :
        {
            console.log("plugin clicked");
            if (plugin_base.getFocusState() === 0)
                plugin_base.askForRoomSelectedFocusState();
            if (plugin_base.getFocusState() === 1)
                plugin_base.askForFocusedFocusState();
        }

        onPressed : {}



        SequentialAnimation {
            id : animation
            running : false
            loops : Animation.Infinite
            NumberAnimation{ target: cube_plugin;
                property: "scale";
                to: 0.95;
                duration : 200;
                easing.type: Easing.InOutElastic
            }
            PauseAnimation { duration: 100 }
            NumberAnimation {
                target: cube_plugin;
                property: "scale";
                to: 1;
                duration : 200;
                easing.type: Easing.InOutElastic
            }
        }
    }
}

// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import QtQuick.Particles 2.0
import "script.js" as Script
import "pocket.js" as Pocket
import "twitter.js" as Twitter
import "storage.js" as Storage
import "translate.js" as AzureTranslate

Item3D
{
    id : testplugin_container

    property real zRot : 1;
    property real yRot : 0;
    property color col : "red";
    property int savedX;
    property int savedY;
    property real savedXPos;
    property real savedYPos;
    property vector3d savedCameraOrientation;

    function getTimeLine()
    {
        console.log("CALL TWITTER <<<<<<<<<<<<<<<<<<<<<");
        Script.requestToken();
        Script.getTwitterTimeAndToken();

        //  Twitter.login();
        console.log("<<<------------------");
        // Script.requestToken();
    }
    // HAS TO BE IMPLEMENTED TO HANDLE STATE CHANGE
    // USE FOR LOGIC CHANGE, FOR ANIMATION USE RATHER STATES
    function focusStateChanged(focusStateValue)
    {
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
    position : Qt.vector3d(0, 0, 0)
    // HAS TO BE IMPLEMENTED
    function roomEntered()    {}
    // HAS TO BE IMPLEMENTED
    function roomLeft()    {}
    // HAS TO BE IMPLEMENTED
    function switchToIdleFocusView()    {plugin_base.moveCamera()}
    // HAS TO BE IMPLEMENTED
    function switchToSelectedFocusView()    {}
    // HAS TO BE IMPLEMENTED
    function switchToFocusedView()
    {
        var eyePos = plugin_base.getRoomPosition();
        eyePos.z += (-10)

        var widgetPos = plugin_base.getRoomPosition();
        widgetPos.x += testplugin_container.x
        widgetPos.y += testplugin_container.y
        widgetPos.z += testplugin_container.z
        plugin_base.moveCamera(eyePos, widgetPos);
    }

    function setColorAssign(msg) {
        console.log("SET COLOR From DB  :  " + msg);
        cube_plugin.effect.color = msg;
        col = msg;
    }

    states : [
        State {
            name : "idle"
            PropertyChanges {target: testplugin_container; col : TestPlugin.getColor()}
            when : plugin_base.getFocusState() === 0
        },
        State {
            name : "selected"
            PropertyChanges {target: testplugin_container; col : TestPlugin.getColor()}
            when : plugin_base.getFocusState() === 1
        },
        State {
            name : "focused"
            PropertyChanges {target: testplugin_container; col : TestPlugin.getColor()}
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
            onClicked:{TestPlugin.selectColor("orange");cube_plugin.effect.color = "orange";}
        }

        Cube
        {
            id : cube_red
            effect: Effect {color: "red"}
            scale : 1
            position : Qt.vector3d(2, 1, 1)
            onClicked:{TestPlugin.selectColor("red");cube_plugin.effect.color = "red";getTimeLine();}
        }

        Cube
        {
            id : cube_blue
            effect: Effect {color: "blue"}
            scale : 1
            position : Qt.vector3d(-2, 1, 0)
            onClicked:{TestPlugin.selectColor("blue");cube_plugin.effect.color = "blue";}
        }
    }

    Item3D
    {
        id : cube_plugin
        mesh: Mesh { source: "./Batman.obj" }
        scale : 0.03
        position : Qt.vector3d(0, -5, 0)
        effect: Effect {color :TestPlugin.getColor(); useLighting : true}
        // APPLY TRANSFORMATIONS SO THAT PLUGIN MODEL FACES US
        transform : [Rotation3D {angle : 180; axis : Qt.vector3d(0, 1, 0)}]

        onClicked :
        {
            console.log("plugin clicked");
            if (plugin_base.getFocusState() === 0)
                plugin_base.askForRoomSelectedFocusState();
            if (plugin_base.getFocusState() === 1)
                plugin_base.askForFocusedFocusState();
        }

        onPressed :
        {
             getTimeLine()
            console.log("Plugin Pressed")
            savedX = -10000;
            savedY = -10000;
        }

        onHoverMove :
        {
            console.log("Hover Moved Signal has been triggered " + x + " " + y);
            console.log("Item Pos " + cube_plugin.position)
            if (savedX === -10000 && savedY === -10000)
            {
                console.log("-------------")
                savedX = x;
                savedY = y;
                savedXPos = cube_plugin.x
                savedYPos = cube_plugin.y


                savedCameraOrientation = plugin_base.getCameraOrientation();
                console.log("><><><><> " + savedCameraOrientation + " " + savedXPos + " " + savedYPos)
            }
            else
            {
//                var xDiff = ((x  * savedXPos) / savedX);
//                var yDiff = ((y  * savedYPos) / savedY);
//                cube_plugin.x = xDiff;
//                cube_plugin.y = yDiff;

                var xRatio = plugin_base.getRoomScale().x / mainWindow.width;
                var yRatio = plugin_base.getRoomScale().y / mainWindow.height;

                var xDiff = (xRatio * x) - (plugin_base.getRoomScale().x / 2);
                var yDiff = (yRatio * y) - (plugin_base.getRoomScale().y / 2);
                console.log("xDiff " + xDiff + " yDiff " + yDiff + " xRatio " + xRatio + " yRatio " + yRatio);

                cube_plugin.x = (savedXPos - xDiff);
//                cube_plugin.y += (savedYPos - yDiff);

                console.log("Item Pos After" + cube_plugin.position)

            }

            // GET ITEM AXIS ON WHICH IT CAN MOVE
            // ITEM POS VALUE ON AXIS / WINDOW WIDTH IF X
            // ITEM POS VALUE ON AXIS / WINDOW WIDTH IF Y
        }

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



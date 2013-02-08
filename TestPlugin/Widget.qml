// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import QtQuick.Particles 2.0

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
    function setColorAssign(msg) {
        console.log("SET COLOR From DB  :  " + msg);
        cube_plugin.effect.color = msg;
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

    //    Carousel
    //    {
    //        id : carousel
    //        scale : 5
    //        radius : 3
    //    }

    states : [
        State {
            name : "idle"
            PropertyChanges {target: testplugin_container; col : apc.getColor()}
            when : plugin_base.getFocusState() == 0
        },
        State {
            name : "selected"
            PropertyChanges {target: testplugin_container; col : apc.getColor()}
            when : plugin_base.getFocusState() == 1
        },
        State {
            name : "focused"
            PropertyChanges {target: testplugin_container; col : apc.getColor()}
            when : plugin_base.getFocusState() == 2
        }
    ]
    Cube
    {
        id : cube_orange
        effect: Effect {color: "orange"}
        scale : 2
        position : Qt.vector3d(0, 0, -3)
        onClicked:{apc.selectColor("orange");cube_plugin.effect.color = "orange";}
    }

    Cube
    {
        id : cube_blue

        effect: Effect {color: "blue"}
        scale : 2
        position : Qt.vector3d(-3, 0, 0)
        onClicked:{apc.selectColor("blue");cube_plugin.effect.color = "blue";
        }
    }

    Cube
    {
        id : cube_red
        effect: Effect {color: "red"}
        scale : 2
        position : Qt.vector3d(3, 0, 0)
        onClicked:{apc.selectColor("red");cube_plugin.effect.color = "red";

        }
    }

    Cube
    {
        id : cube_plugin
        //        scale : 5
        transform : [Scale3D {scale : Qt.vector3d(5, 10, 5)} ]
        position : Qt.vector3d(0, 0, 0)
        effect: Effect {color :col; useLighting : true}
        //        transform : [Rotation3D {angle : zRot; axis : Qt.vector3d(0, 0, 1)},
        //            Rotation3D {angle : yRot; axis : Qt.vector3d(0, 1, 0)}]

        scale : (pressed) ? 0.9 : 1
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


        //    Timer
        //    {
        //        running : true
        //        repeat: true
        //        interval: 25
        //        onTriggered:
        //        {
        //            zRot += 1
        //            yRot += 1
        //        }
        //    }

        property real pressedTime : 0;
        onClicked :
        {
            // IF WE ARE IDLING ON CLICK ASK FOR SELECTED
            if (plugin_base.getFocusState() == 0)
            {
                console.log("Asking for selected");
                plugin_base.askForRoomSelectedFocusState();
            } // IF WE ARE SELECTED ASK FOR FOCUS
            else if (plugin_base.getFocusState() == 1)
            {
                console.log("Asking for focused");
                plugin_base.askForFocusedFocusState();
            }
            else    // FOCUSED STATE
            {

            }
        }

        //onHoverEnter :    {col = "orange";console.log("Hover");}
        //onHoverLeave :    {col = "red"}
        onPressed :    {console.log("pressed"); pressedTime = new Date().getTime()}
        onReleased :   {
            //            if (new Date().getTime() - pressedTime > 2000)
            //            {
            //                col = "blue"; pressedTime = 0;
            //                animation.running = true;
            //            }
        }
        onDoubleClicked :    {console.log("x,y,z " + x + "," + y + "," + z);}
    }
}

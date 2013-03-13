// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import QtQuick.Particles 2.0

Item3D
{
    id : watchMain

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
        center.x += watchMain.x
        center.y += watchMain.y
        center.z += watchMain.z
        plugin_base.moveCamera(eye, center);
    }



    states : [
        State {
            name : "idle"
            PropertyChanges {target: watchMain;}
            when : plugin_base.getFocusState() === 0
        },
        State {
            name : "selected"
            PropertyChanges {target: watchMain; }
            when : plugin_base.getFocusState() === 1
        },
        State {
            name : "focused"
            PropertyChanges {target: watchMain;}
            when : plugin_base.getFocusState() === 2
        }
    ]
    Item3D
    {
        id : background_plugin
        mesh: Mesh { source: "officeclock.3DS" }
//effect: Effect {color :"blue"; useLighting : true}
        position : Qt.vector3d(1, 0, 0)
        transform: [
            Rotation3D {
                id: rotateB
                angle: 90
                axis: Qt.vector3d(0, 0, 1)
            }]
        scale : 0.07

        onClicked :
        {
            console.log("plugin clicked");
            if (plugin_base.getFocusState() === 0)
                plugin_base.askForRoomSelectedFocusState();
            if (plugin_base.getFocusState() === 1)
                plugin_base.askForFocusedFocusState();
        }
    }


    Item3D{
         id: clock
         property int hours
         property int minutes
         property int seconds
         property real shift
         property bool night: false
         function timeChanged() {
             var date = new Date;
             hours = shift ? date.getUTCHours() + Math.floor(clock.shift) : date.getHours()
             night = ( hours < 7 || hours > 19 )
             minutes = shift ? date.getUTCMinutes() + ((clock.shift % 1) * 60) : date.getMinutes()
             seconds = date.getUTCSeconds();
         }

    Item3D
    {
        id : minutes

        mesh: Mesh { source: "Clock_Wall_2.dae" }
        effect: Effect {color :"red"; useLighting : true}

        position : Qt.vector3d(1, 0, 0)
        transform: [
            Rotation3D {
                id: rotate_minutes
                angle: 90
                axis: Qt.vector3d(0, 0, 1)
            }]
        scale : (pressed) ? 0.9 : 1

        onClicked :
        {
            console.log("plugin clicked");
            if (plugin_base.getFocusState() === 0)
                plugin_base.askForRoomSelectedFocusState();
            if (plugin_base.getFocusState() === 1)
                plugin_base.askForFocusedFocusState();
        }
    }

    Item3D
    {
        id : hours

        mesh: Mesh { source: "Clock_Wall_3.dae" }

        effect: Effect {color :"red"; useLighting : true}
        position : Qt.vector3d(1, 0, 0)

        scale : (pressed) ? 0.9 : 1
        transform: Rotation3D {
            id: hourRotation
            origin.x: 7.5; origin.y: 73;
            angle: 90 + ((clock.hours * 30) + (clock.minutes * 0.5))
            Behavior on angle {
                SpringAnimation { spring: 2; damping: 0.2; modulus: 360 }
            }
            axis: Qt.vector3d(0, 0, 1)
        }
        onClicked :
        {
            console.log("plugin clicked");
            if (plugin_base.getFocusState() === 0)
                plugin_base.askForRoomSelectedFocusState();
            if (plugin_base.getFocusState() === 1)
                plugin_base.askForFocusedFocusState();
        }
    }




}
}



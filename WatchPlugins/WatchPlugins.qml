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
        id : cube_plugin
        position : Qt.vector3d(-9, -5, 0)
        scale : (pressed) ? 0.9 : 1
        onClicked :
        {
            console.log("plugin clicked");
            if (plugin_base.getFocusState() === 0)
                plugin_base.askForRoomSelectedFocusState();
            if (plugin_base.getFocusState() === 1)
                plugin_base.askForFocusedFocusState();
        }

        Clock { city: "New York"; shift: -4 }

    }
}



// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0


//Item3D
//{
//    scale:0.2
//    position:Qt.vector3d(0,1.5,6)
//    mesh : Mesh {source:"Resources/Models/dog.3ds"}
//}

Item3D
{
    property real zRot : 0;
    property real yRot : 0;
    property color col : "red"

    // HAS TO BE IMPLEMENTED TO HANDLE STATE CHANGE
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
    function switchToFocusedView()    {plugin_base.moveCamera()}

    //    Carousel
    //    {
    //        id : carousel
    //        scale : 5
    //        radius : 3
    //    }

    Behavior on x { NumberAnimation {duration : 200}}
    Behavior on y { NumberAnimation {duration : 200}}
    Behavior on z { NumberAnimation {duration : 200}}

    Cube
    {
        id : cube_plugin

        scale : 5
        position : Qt.vector3d(0, 0, 0)
        effect: Effect {color :col; useLighting : true}
        //        transform : [Rotation3D {angle : zRot; axis : Qt.vector3d(0, 0, 1)},
        //            Rotation3D {angle : yRot; axis : Qt.vector3d(0, 1, 0)}]

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

        onHoverEnter :    {col = "orange";console.log("Hover");}
        onHoverLeave :    {col = "red"}
        onPressed :    {console.log("pressed"); pressedTime = new Date().getTime()}
        onReleased :   {if (new Date().getTime() - pressedTime > 2000) {col = "blue"; pressedTime = 0;}}
        onDoubleClicked :    {console.log("x,y,z " + x + "," + y + "," + z);plugin_base.askForFocusedFocusState();}
    }
}

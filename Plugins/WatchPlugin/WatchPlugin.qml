import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0



Item3D
{
    id : alarm_clock_container
    position : Qt.vector3d(0, 0, 0)
    property bool isFocused : false;
    // HAS TO BE IMPLEMENTED
    function roomEntered()    {}
    // HAS TO BE IMPLEMENTED
    function roomLeft()    {}
    // HAS TO BE IMPLEMENTED
    function switchToIdleFocusView()    {plugin_base.moveCamera();}
    // HAS TO BE IMPLEMENTED
    function switchToSelectedFocusView()    {isFocused = false}
    // HAS TO BE IMPLEMENTED
    function switchToFocusedView()
    {
        var eyePos = plugin_base.getRoomPosition();
        eyePos.z += (-10)

        var widgetPos = plugin_base.getRoomPosition();
        widgetPos.x += alarm_clock_container.x
        widgetPos.y += alarm_clock_container.y
        widgetPos.z += alarm_clock_container.z
        plugin_base.moveCamera(eyePos, widgetPos);
        isFocused = true;
    }


    Item3D
    {
        id : modelAlarm
        mesh: Mesh { source: "./AlarmClock-1.dae" }
        scale : 5
        position : Qt.vector3d(2, -2, 0)
        transform : [Rotation3D { angle : 180; axis : Qt.vector3d(1, 0, 0)}]

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

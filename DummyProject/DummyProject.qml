import QtQuick 2.1
import Qt3D 2.0
import Qt3D.Shapes 2.0

Item3D
{
    id : DummyProject_item


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
        widgetPos.x += DummyProject_container.x
        widgetPos.y += DummyProject_container.y
        widgetPos.z += DummyProject_container.z
        plugin_base.moveCamera(eyePos, widgetPos);
    }

    Item3D
    {
        id : DummyProject_container
    }
}

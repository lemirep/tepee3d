import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0

Item3D
{
    id : xbmcplugin_item

    property bool isFocused : false;

    // HAS TO BE IMPLEMENTED
    function roomEntered()    {}
    // HAS TO BE IMPLEMENTED
    function roomLeft()    {}
    // HAS TO BE IMPLEMENTED
    function switchToIdleFocusView()    {plugin_base.moveCamera(); isFocused = false}
    // HAS TO BE IMPLEMENTED
    function switchToSelectedFocusView()    {isFocused = false}
    // HAS TO BE IMPLEMENTED
    function switchToFocusedView()
    {
        var eyePos = plugin_base.getRoomPosition();
        eyePos.z += (-10)

        var widgetPos = plugin_base.getRoomPosition();
        widgetPos.x += plugin_base.pluginPosition.x
        widgetPos.y += plugin_base.pluginPosition.y
        widgetPos.z += plugin_base.pluginPosition.z
        var up = Qt.vector3d(0, 1, 0)
        plugin_base.moveCamera(eyePos, widgetPos, up);
        isFocused = true;
    }

    Sphere
    {
        scale : 5
        levelOfDetail : 6
        effect : Effect {
            color : "red"
        }
        onClicked : {plugin_base.askForFocusedFocusState()}
    }

    Home
    {
        id : home_item
        enabled : (opacity === 1)
        opacity : isFocused ? 1 : 0
    }
}

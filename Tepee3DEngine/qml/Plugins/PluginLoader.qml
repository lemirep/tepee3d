import QtQuick 2.1
import Qt3D 2.0

Item3D
{
    id : plugin_loader_item
    property alias source : widget_loader.source
    property int pluginId : 0
    property string roomQmlFile : ""
    property string focusedQmlFile : ""
    property string pluginName : ""

    Loader
    {
        id : widget_loader

        function getPluginName() {return plugin_loader_item.pluginName}
        function getPluginId()   {return plugin_loader_item.pluginId}
        function getPluginRoomQmlFile() {return plugin_loader_item.roomQmlFile}
        function getPluginFocusedQmlFile() {return plugin_loader_item.focusedQmlFile}

        onProgressChanged:
        {
            // console.log("source " + source);
        }
        onLoaded:
        {
            console.log("Plugin Model Loaded");
        }
    }
}

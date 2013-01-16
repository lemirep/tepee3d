import QtQuick 2.0
import Qt3D 2.0
import Plugins 1.0


Item3D
{
    id : plugin_base

    property int pluginId : widget_loader.getPluginId()
    property string roomQmlFile : widget_loader.getPluginRoomQmlFile()
    property string focusedQmlFile : widget_loader.getPluginFocusedQmlFile()
    property string pluginName : widget_loader.getPluginName()

    // TO ASK FOR A GIVEN FOCUS STATE CALL
    // plugin_base.askForFocusState(State)
    // IF CHANGE ACCEPTED, onFocusStateChanged will be called

    PluginProperties
    {
        id : plugin_properties
        pluginId : plugin_base.pluginId
        onPluginIdChanged :        {}

        onFocusStateChanged:
        {
            console.log("v State " + newFocusStateValue + "  "  + focusState);
            switch (newFocusStateValue)
            {
            case 0 : //PluginEnums.pluginIdleState :
                plugin_loader.source =  "../../plugins_qml/" + pluginName + "/" + roomQmlFile;
                break;
            case 1 : //PluginEnums.pluginSelectedState:
                break;
            case 2 : //PluginEnums.pluginFocusedState :
                plugin_loader.source =  "../../plugins_qml/" + pluginName + "/" + focusedQmlFile;
                break;
            default:
                break;
            }
        }
    }

    Loader
    {
        id : plugin_loader
    }

}

import QtQuick 2.0
import Qt3D 2.0
import Plugins 1.0


Item3D
{
    id : plugin_base

    property int pluginId : -1
    property int pluginRoomId :-1
    property string roomQmlFile : ""
    property string focusedQmlFile : ""
    property string pluginName : ""

    // TO ASK FOR A GIVEN FOCUS STATE CALL
    // plugin_base.askForFocusState(State)
    // IF CHANGE ACCEPTED, onFocusStateChanged will be called

    function askForFocusedFocusState()
    {
        plugin_properties.askForFocusState(2)
    }

    function askForRoomFocusState()
    {
        PluginProperties.askForFocusState(0)
    }

    PluginProperties
    {
        id : plugin_properties
        pluginId : plugin_base.pluginId
        pluginRoomId: plugin_base.pluginRoomId

        onPluginIdChanged :        {}

        onPluginRoomIdChanged: {console.log("RoomId " + pluginRoomId)}

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
//                plugin_loader.source =  "../../plugins_qml/" + pluginName + "/" + focusedQmlFile;
                plugin_loader.source =  "";
                break;
            default:
                break;
            }
        }

        onRoomEntered :
        {
            console.log("Room Entered ???");
        }

        onRoomLeft :
        {
            console.log("Room Left ????");
        }
    }

    Loader
    {
        id : plugin_loader

        onSourceChanged:
        {
            console.log("source changed " + source)
        }
    }

}

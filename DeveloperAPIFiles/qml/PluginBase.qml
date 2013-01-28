import QtQuick 2.0
import Qt3D 2.0
import Plugins 1.0
import "../js/CameraManagement.js" as CameraManagement

Item3D
{
    id : plugin_base

    property int pluginId : -1
    property int pluginRoomId :-1
    property string roomQmlFile : ""
    property string menuQmlFile : ""
    property string pluginName : ""

    // TO ASK FOR A GIVEN FOCUS STATE CALL
    // plugin_base.askForFocusState(State)
    // IF CHANGE ACCEPTED, onFocusStateChanged will be called

    function askForRoomFocusState()            {plugin_properties.askForFocusState(0)}
    function askForRoomSelectedFocusState()    {plugin_properties.askForFocusState(1)}
    function askForFocusedFocusState()         {plugin_properties.askForFocusState(2)}
    function getFocusState()                   {return plugin_properties.focusState}
    function moveCamera(eye, center, up)       {CameraManagement.moveCamera(camera, eye, center, up)}
    // RETURN DEEP COPY OF VAR SO THEY CANNOT MODIFY THE ROOM DIRECTLY
    function getRoomPosition()                 {return room_item.getRoomPosition()}
    function getRoomScale()                    {return room_item.getRoomScale()}


    PluginProperties
    {
        id : plugin_properties
        pluginId : plugin_base.pluginId
        pluginRoomId: plugin_base.pluginRoomId

        onPluginIdChanged :        {}

        onPluginRoomIdChanged: {console.log("RoomId " + pluginRoomId)}

        // WHEN CREATED A PLUGIN IS NOT LOADED BEFORE IT HAS BEEN INITIALIZED WITH A pluginId AND A roomId
        // ONCE THAT IS DONE, THE FOCUS STATE IS SET TO IDLE
        // IF THE LOADER HAS NOT LOADED ANY ELEMENT YET THEN IT LOADS THE PLUGINS
        // OTHERWISE IT TRANSMITS THE SIGNAL TO THE PLUGIN ITEM


        onFocusStateChanged:
        {
            console.log("v State " + newFocusStateValue + "  "  + focusState);
            switch (newFocusStateValue)
            {
            case 0 : //PluginEnums.pluginIdleState :
                if (!plugin_loader.item)
                    plugin_loader.source =  "../../plugins_qml/" + pluginName + "/" + roomQmlFile;
                else
                    plugin_loader.item.focusStateChanged(newFocusStateValue);
                break;
            case 1 : //PluginEnums.pluginSelectedState:
                if (plugin_loader.item)
                    plugin_loader.item.focusStateChanged(newFocusStateValue);
                break;
            case 2 : //PluginEnums.pluginFocusedState :
                if (plugin_loader.item)
                    plugin_loader.item.focusStateChanged(newFocusStateValue);
                break;
            default:
                break;
            }
        }

        onRoomEntered :
        {
            console.log("Room Entered ???");
            if (plugin_loader.item)
                plugin_loader.item.roomEntered();
        }

        onRoomLeft :
        {
            if (plugin_loader.item)
                plugin_loader.item.roomLeft();
            console.log("Room Left ????");
        }
    }

    Loader
    {
        id : plugin_loader

        onLoaded: {        }
    }

}

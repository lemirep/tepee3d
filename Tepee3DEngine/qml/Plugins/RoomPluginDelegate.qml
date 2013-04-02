import QtQuick 2.0

Item
{
    id : item_plugin_del
    property string pluginName;
    property int    pluginId;

    anchors.horizontalCenter: parent.horizontalCenter
    scale : plugin_delegate_mouse_area.pressed ? 0.9 : 1.0
    Behavior on scale {SmoothedAnimation {velocity : 1; duration : -1}}

    MouseArea
    {
        id : plugin_delegate_mouse_area
        anchors.fill : parent
        onClicked :
        {
            room_plugins_list_view.currentIndex = index;
            // ASK THE CURRENT ROOM TO SET THE PLUGIN TO THE FOCUSED FOCUSSTATE
            roomManager.askFocusStateForPlugin(pluginId, 2);
        }
        onPressAndHold:
        {
            if (room_plugins_list_view.currentIndex === index)
                room_plugins_list_view.currentIndex = -1;
            roomManager.removePluginFromCurrentRoom(pluginId)
        }
    }

    BorderImage
    {
        id: delRect
        source: (room_plugins_list_view.currentIndex == index) ?  "../Resources/Pictures/delegate_selected.png" : "../Resources/Pictures/delegate.png"
        anchors.fill: parent
        Behavior on rotation {SpringAnimation {spring: 30; damping: 0.3; mass: 1.0}}
    }

    Text
    {
        id: plugin_title
        text: pluginName
        anchors.centerIn: delRect
        color :  "white"
    }
}

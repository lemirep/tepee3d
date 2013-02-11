import QtQuick 2.0

Item
{
    id : item_plugin_del
    anchors.horizontalCenter: parent.horizontalCenter
    scale : plugin_delegate_mouse_area.pressed ? 0.9 : 1.0

    property string pluginName : ""

    MouseArea
    {
        id : plugin_delegate_mouse_area
        anchors.fill : parent
        onClicked :
        {
            room_plugins_list_view.currentIndex = index;
            // SET SELECTED PLUGIN AS FOCUSED PLUGIN
        }
    }

    Rectangle
    {
        color : (room_plugins_list_view.currentIndex == index) ? mainWindow.plugin_list_selected_component_color: mainWindow.plugin_list_component_color
        anchors.fill: parent
    }

    Text
    {
        id: plugin_title
        text: pluginName
        anchors
        {
            horizontalCenter : parent.horizontalCenter
            bottom : parent.bottom
            margins : 10
        }
        color :  "white"
    }
}

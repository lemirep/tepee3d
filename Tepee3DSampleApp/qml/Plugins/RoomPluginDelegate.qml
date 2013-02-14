import QtQuick 2.0

Item
{
    id : item_plugin_del
    property string pluginName : ""

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
            // SET SELECTED PLUGIN AS FOCUSED PLUGIN
        }
    }

    BorderImage
    {
        id: delRect
        source: (room_plugins_list_view.currentIndex == index) ?  "../Resources/Pictures/delegate_selected.png" : "../Resources/Pictures/delegate.png"
        anchors.fill: parent
//        border.left: 5; border.top: 5
//        border.right: 5; border.bottom: 5
        Behavior on rotation {SpringAnimation {spring: 30; damping: 0.3; mass: 1.0}}
    }
//    Rectangle
//    {
//        color : (room_plugins_list_view.currentIndex == index) ? mainWindow.plugin_list_selected_component_color: mainWindow.plugin_list_component_color
//        anchors.fill: parent
//    }

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

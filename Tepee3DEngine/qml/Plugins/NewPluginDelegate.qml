import QtQuick 2.1

Item
{
    id : item_plugin_del
    property string pluginName : ""
    property bool downloaded : false;
    property bool downloading : false;
    property bool online : false
    property bool error : false;

    anchors.horizontalCenter: parent.horizontalCenter
    scale : plugin_delegate_mouse_area.pressed ? 0.9 : 1.0
    Behavior on scale {SmoothedAnimation {velocity : 1; duration : -1}}

    onDownloadedChanged:
    {
        console.log("<<<<<<<<<<< DOWNLOADED CHANGED " << downloaded);
    }

    onDownloadingChanged:
    {
        console.log("<<<<<<<<<<< DOWNLOADED CHANGED " << downloading);
    }

    MouseArea
    {
        id : plugin_delegate_mouse_area
        anchors.fill : parent
        onClicked :
        {
            if (!online)
            {
                room_plugins_list_view.currentIndex = index;
                console.log("Plugin ID " + model.pluginId)
                roomManager.addNewPluginToCurrentRoom(model.pluginId)
                menuRightRec.add_plugins = !menuRightRec.add_plugins
            }
            else
            {
                pluginManager.downloadPluginFromServer(model.pluginId)
            }
        }
    }

    BorderImage
    {
        id: delRect
        source: (room_plugins_list_view.currentIndex === index) ?  "../Resources/Pictures/delegate_selected.png" : "../Resources/Pictures/delegate.png"
        anchors.fill: parent
        Behavior on rotation {SpringAnimation {spring: 30; damping: 0.3; mass: 1.0}}
    }

    Text
    {
        id: plugin_title
        text: pluginName
        //        width : delRect.width
        elide : Text.ElideMiddle
        font.pixelSize: mainWindow.defaultFontSize
        anchors.centerIn: delRect
        color :  "white"
    }


    Image
    {
        Rectangle
        {
            color : "red"
            anchors.fill: parent
            opacity : (error) ? 1 : 0
        }

        id : download_arrow
        fillMode: Image.PreserveAspectFit
        opacity : (downloaded || downloading) ? 1.0 : 0
        y : delRect.height / 2
        height : delRect.height / 2
        scale : downloaded ? 0.7 : 1
        Behavior on scale {SmoothedAnimation {velocity : 1; duration : -1}}
        Behavior on opacity {SmoothedAnimation {velocity : 1; duration : -1}}
        anchors
        {
            right : parent.right
            rightMargin : 5
        }
        source : "../Resources/Pictures/download_arrow.png"

        SequentialAnimation
        {
            loops: Animation.Infinite
            running : downloading && menuRightMain.isShown
            alwaysRunToEnd: true
            ParallelAnimation
            {
                NumberAnimation { target: download_arrow; property: "opacity"; to : 0; duration: 1000; easing.type: Easing.InOutQuad }
                NumberAnimation { id : end_animation; target: download_arrow; property: "y"; to : delRect.height / 2 + 30; duration: 1000; easing.type: Easing.InOutQuad }
            }
            NumberAnimation { id : beg_animation; target: download_arrow; property: "y"; to : delRect.height / 2; duration: 100; easing.type: Easing.InOutQuad }
            NumberAnimation { target: download_arrow; property: "opacity"; to : 1; duration: 100; easing.type: Easing.InOutQuad }
        }
    }

}


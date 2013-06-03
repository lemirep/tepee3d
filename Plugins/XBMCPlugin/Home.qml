import QtQuick 2.0
import QtGraphicalEffects 1.0

Item
{
    id : home_elem
    width : mainWindow.width
    height : mainWindow.height

    ListModel
    {
        id : menu_model
        ListElement {picture : "remote.png"; libraryFile : "RemoteItem.qml"}
        ListElement {picture : "music.png"; libraryFile : "AudioLibrary.qml"}
        ListElement {picture : "shows.png"; libraryFile : "ShowsLibrary.qml"}
        ListElement {picture : "movies.png"; libraryFile : "MoviesLibrary.qml"}
    }

    Item
    {
        id : content_item
        anchors
        {
            fill : parent
            topMargin : 50
            leftMargin : 50
            rightMargin : 50
            bottomMargin : 150
        }

        ListView
        {
            id : main_listview
            anchors.fill: parent
            model : menu_model
            orientation: ListView.Horizontal
            clip : true
            highlightMoveDuration : 750
            snapMode : ListView.SnapOneItem
            delegate : Component {
                Item
                {
                    width : main_listview.width
                    height : main_listview.height
                    Loader
                    {
                        id : delegate_loader
                        anchors.fill: parent
                        source : model.libraryFile
                    }
                }
            }
            highlightRangeMode: ListView.StrictlyEnforceRange
            preferredHighlightBegin: 0
            preferredHighlightEnd: width
            onCurrentIndexChanged: {menu_button_listview.currentIndex = main_listview.currentIndex;}
        }
    }

    Item
    {
        id : menu_bar
        anchors
        {
            left : content_item.left
            right : content_item.right
            top : content_item.bottom
            bottom : parent.bottom
            bottomMargin : 50
        }
        Rectangle
        {
            anchors.fill: parent
            color : "black"
            opacity : 0.4
        }
        Image
        {
            source : "shadow_separator_h.png"
            width : parent.width
        }
        ListView
        {
            id : menu_button_listview
            anchors.fill: parent
            orientation: ListView.Horizontal
            model : menu_model
            interactive : false
            delegate : Component {
                Item
                {
                    id : remote_menu_button
                    height : menu_button_listview.height
                    width : menu_button_listview.width / menu_model.count
                    MouseArea
                    {
                        id : menu_delegate_ma
                        anchors.fill: parent
                        onClicked: {menu_button_listview.currentIndex = index; main_listview.currentIndex = index}
                    }
                    Image
                    {
                        id : logo
                        scale : menu_delegate_ma.pressed ? 0.9 : 1
                        fillMode: Image.PreserveAspectFit
                        height: parent.height
                        source : model.picture
                        anchors.centerIn: parent
                    }
                    Glow
                    {
                        visible : (index === menu_button_listview.currentIndex)
                        anchors.fill: logo
                        radius: 8
                        color: "blue"
                        source: logo
                        fast : true
                        spread : 0.3
                    }
                }
            }
        }
    }
}

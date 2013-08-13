import QtQuick 2.1

Item
{
    anchors.fill: parent

    ListModel
    {
        id : audio_model
        ListElement
        {
            name : "Artists"
            sourceElem : "ArtistLibrary.qml"
        }
        ListElement
        {
            name : "Albums"
            sourceElem : "AlbumsLibrary.qml"
        }
        ListElement
        {
            name : "Songs"
            sourceElem : "SongsLibrary.qml"
        }
    }


    ListView
    {
        id : top_banner_listview
        anchors
        {
            top : parent.top
            left : parent.left
            right : parent.right
        }
        height: 50
        model : audio_model
        interactive: false;
        orientation: ListView.Horizontal
        delegate : Component {
            Item
            {
                width : top_banner_listview.width / 3
                height: top_banner_listview.height
                Rectangle
                {
                    anchors.fill: parent
                    color : "black"
                    opacity : (index === top_banner_listview.currentIndex) ? 0.3 : 0.1
                    border
                    {
                        width : 1
                        color : "white"
                    }
                }
                Text
                {
                    id : text_sort
                    anchors.centerIn: parent
                    text : model.name
                    color : "white"
                    font.pixelSize: mainWindow.largeFontSize
                }
                MouseArea
                {
                    anchors.fill: parent
                    onClicked: {audio_content_listview.currentIndex = index; top_banner_listview.currentIndex = index}
                }
            }
        }
    }
    ListView
    {
        id : audio_content_listview
        orientation: ListView.Vertical
        model : audio_model
        interactive: false
        clip : true
        anchors
        {
            top : top_banner_listview.bottom
            left : parent.left
            right : parent.right
            bottom : parent.bottom
        }
        delegate: Component {
            Loader
            {
                opacity : (index === audio_content_listview.currentIndex) ? 1 : 0
                enabled : (opacity === 1)
                Behavior on opacity {NumberAnimation {duration : 750}}
                width: audio_content_listview.width
                height: audio_content_listview.height
                source : model.sourceElem
            }
        }
        highlightRangeMode: ListView.StrictlyEnforceRange
        preferredHighlightBegin: 0
        preferredHighlightEnd: height
        snapMode: ListView.SnapOneItem
    }

}

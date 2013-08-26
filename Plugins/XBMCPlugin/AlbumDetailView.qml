import QtQuick 2.1

Item
{
    id : album_view
    property int albumId;
    property alias thumbnail : album_thumbnail.source
    property alias albumTitle : album_title_text.text
    property alias albumSummary : album_summary.text
    property alias songModel : album_songs_listview.model
    signal backButtonClicked();
    clip : true

    Item
    {
        id : album_detail_item
        width : parent.width / 3
        anchors
        {
            left : parent.left
            top : parent.top
            bottom   : parent.bottom
        }
        clip : true
        Rectangle
        {
            anchors.fill: parent
            smooth : true
            border
            {
                width : 1
                color : "white"
            }
            color : "black"
            opacity : 0.1
            radius : 5
        }
        Item
        {
            id : thumbnail_shadow_item
            width : album_thumbnail.paintedWidth
            height : album_thumbnail.paintedHeight
            anchors.centerIn: album_thumbnail
        }

        Rectangle
        {
            width : album_thumbnail.paintedWidth
            height : album_thumbnail.paintedHeight
            anchors
            {
                top : thumbnail_shadow_item.top
                left : thumbnail_shadow_item.left
                leftMargin : 8
                topMargin : 8
            }
            radius : 2
            color : "#44000000"
            scale : album_thumbnail.scale
        }
        Image
        {
            id : album_thumbnail
            width: parent.width - 40
            fillMode: Image.PreserveAspectFit
            Behavior on scale {NumberAnimation {duration : 1200; easing.type: Easing.InOutBack}}
            scale : (status == Image.Ready) ? 1 : 0
            anchors
            {
                top : parent.top
                topMargin : 20
                horizontalCenter : parent.horizontalCenter
            }
        }
        AddButton
        {
            width : 50
            scale : Math.min(album_thumbnail.scale, pressed ? 0.9 : 1)
            anchors
            {
                right : album_thumbnail.right
                bottom : album_thumbnail.bottom
            }
            onClicked : {xbmc_plugin.addAlbumToPlaylist(albumId)}
        }
        Text
        {
            id : album_title_text
            width : parent.width
            clip : true
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            horizontalAlignment: Text.AlignHCenter
            color : "white"
            anchors
            {
                top : album_thumbnail.bottom
                topMargin : 15
                horizontalCenter : parent.horizontalCenter
            }
            font.pixelSize: mainWindow.largeFontSize
        }
        Flickable
        {
            anchors
            {
                top : album_title_text.bottom
                topMargin : 5
                bottom : parent.bottom
                left : parent.left
                right : parent.right
            }
            clip : true
            contentWidth: width
            contentHeight: album_summary.height
            Text
            {
                id : album_summary
                color : "white"
                font.pixelSize: mainWindow.defaultFontSize
            }
        }
    }
    ListView
    {
        id : album_songs_listview
        clip : true
        anchors
        {
            left : album_detail_item.right
            right : parent.right
            top : parent.top
            bottom : back_button_album_detail.top
            leftMargin : 10
        }
        delegate : Component {
            Item
            {
                width : album_songs_listview.width
                height : album_songs_listview.height / 6

                Image
                {
                    id : song_thumbnail
                    height: parent.height - 20
                    fillMode: Image.PreserveAspectFit
                    Behavior on scale {NumberAnimation {duration : 1200; easing.type: Easing.InOutBack}}
                    scale : (status == Image.Ready) ? 1 : 0
                    anchors
                    {
                        left : parent.left
                        leftMargin : 5
                        verticalCenter : parent.verticalCenter
                    }
                    smooth : true
                    source : (model.thumbnail !== "") ? xbmc_plugin.getXBMCImageProviderUrl(model.thumbnail) : "empty_cd.png"
                }
                Text
                {
                    id : song_title
                    color : "white"
                    width : parent.width / 2
                    wrapMode: Text.WrapAnywhere
                    anchors
                    {
                        left : song_thumbnail.right
                        leftMargin : 15
                        verticalCenter : parent.verticalCenter
                    }
                    font.pixelSize: mainWindow.defaultFontSize
                    text : model.title
                }
                Text
                {
                    id : song_duration
                    color : "white"
                    wrapMode: Text.WrapAnywhere
                    anchors
                    {
                        right : play_button.left
                        verticalCenter : parent.verticalCenter
                        rightMargin : 5
                    }
                    font.pixelSize: mainWindow.defaultFontSize
                    text : Math.floor(((model.runtime % 3600) / 60)) + ":" + Math.floor(((model.runtime % 3600) % 60))
                }
                Image
                {
                    id : play_button
                    height : Math.max(parent.height / 2, 75)
                    fillMode: Image.PreserveAspectFit
                    source : "small_play.png"
                    scale : play_button_ma.pressed ? 0.9 : 1
                    anchors
                    {
                        right : add_playlist_button.left
                        verticalCenter : parent.verticalCenter
                    }
                    MouseArea
                    {
                        id : play_button_ma
                        anchors.fill: parent
                        onClicked:
                        {
                            xbmc_plugin.playFile(model.file)
                        }
                    }
                }
                AddButton
                {
                    id : add_playlist_button
                    height : Math.max(parent.height / 2, 75)
                    anchors
                    {
                        right : parent.right
                        verticalCenter : parent.verticalCenter
                    }

                    onClicked :
                    {
                        xbmc_plugin.addSongToPlaylist(model.songId)
                    }
                }
            }
        }
    }

    BackButton
    {
        id : back_button_album_detail
        width : 50
        onClicked : {backButtonClicked()}
        anchors
        {
            right : parent.right
            bottom : parent.bottom
            margins : 5
        }
    }
}

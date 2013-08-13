import QtQuick 2.1

Item
{
    id : artist_view
    property int artistId
    property alias thumbnail : artist_thumbnail.source
    property alias artistName : artist_title_text.text
    property alias artistAlbumsModel : artists_albums_listview.model
    property bool albumDetailView : false
    signal backButtonClicked()

    clip : true

    states : [
        State
        {
            name : "albums_view"
            AnchorChanges
            {
                target : albums_view
                anchors.right : artist_view.right
            }
            AnchorChanges
            {
                target : album_detail_view_item
                anchors.left: artist_view.right
            }
            when : !albumDetailView
        },
        State
        {
            name : "album_detail_view"
            AnchorChanges
            {
                target : album_detail_view_item
                anchors.left: artist_view.left
            }
            AnchorChanges
            {
                target : albums_view
                anchors.right : artist_view.left
            }
            when : albumDetailView
        }
    ]

    transitions: Transition {
        AnchorAnimation { duration: 250 }
    }

    Item
    {
        id : albums_view

        anchors
        {
            left : parent.left
            top : parent.top
            bottom : parent.bottom
        }
        clip : true
        Item
        {
            id : artist_detail_item
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
                width : artist_thumbnail.paintedWidth
                height : artist_thumbnail.paintedHeight
                anchors.centerIn: artist_thumbnail
            }

            Rectangle
            {
                width : artist_thumbnail.paintedWidth
                height : artist_thumbnail.paintedHeight
                anchors
                {
                    top : thumbnail_shadow_item.top
                    left : thumbnail_shadow_item.left
                    leftMargin : 8
                    topMargin : 8
                }
                radius : 2
                color : "#44000000"
                scale : artist_thumbnail.scale
            }
            Image
            {
                id : artist_thumbnail
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
                scale : Math.min(artist_thumbnail.scale, pressed ? 0.9 : 1)
                anchors
                {
                    right : artist_thumbnail.right
                    bottom : artist_thumbnail.bottom
                }
                onClicked : {XBMCPlugin.addArtistToPlaylist(artistId)}
            }
            Text
            {
                id : artist_title_text
                width : parent.width
                clip : true
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                horizontalAlignment: Text.AlignHCenter
                color : "white"
                anchors
                {
                    top : artist_thumbnail.bottom
                    topMargin : 15
                    horizontalCenter : parent.horizontalCenter
                }
                font.pixelSize: mainWindow.largeFontSize
            }
        }
        GridView
        {
            id : artists_albums_listview
            clip : true
            anchors
            {
                left : artist_detail_item.right
                right : parent.right
                top : parent.top
                bottom : back_button_artist_detail.top
                leftMargin : 10
            }
            cellWidth : width / 4
            cellHeight : cellWidth

            delegate : LibraryGridViewDelegate {
                width : artists_albums_listview.cellWidth
                height : artists_albums_listview.cellHeight
                thumbnail: (model.thumbnail !== "") ? XBMCPlugin.getXBMCImageProviderUrl(model.thumbnail) : "empty_cd.png"
                title : model.albumTitle
                onClicked:
                {
                    albumDetailView = true;
                    album_detail_view.albumId = albumId
                    album_detail_view.thumbnail = thumbnail
                    album_detail_view.albumTitle = title
                    album_detail_view.albumSummary = model.description
                    album_detail_view.songModel = artists_albums_listview.model.subModelFromId(model.albumId)
                }
            }
        }
        BackButton
        {
            id : back_button_artist_detail
            width : 50
            onClicked : {backButtonClicked();}
            anchors
            {
                right : parent.right
                bottom : parent.bottom
                margins : 5
            }
        }
    }

    Item
    {
        id : album_detail_view_item
        anchors
        {
            right : parent.right
            top : parent.top
            bottom : parent.bottom
        }
        AlbumDetailView
        {
            id : album_detail_view
            anchors.fill: parent
            onBackButtonClicked: albumDetailView = false;
        }
    }

}

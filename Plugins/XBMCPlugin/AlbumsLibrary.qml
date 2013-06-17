import QtQuick 2.0

Item
{
    id : album_library_item
    property  bool albumView : false
    anchors.fill: parent
    states : [
        State
        {
            name : "library_view"
            AnchorChanges
            {
                target : albums_library_gridview
                anchors.top: album_library_item.top
            }
            AnchorChanges
            {
                target : album_view
                anchors.bottom : album_library_item.top
            }
            when : !albumView
        },
        State
        {
            name : "album_view"
            AnchorChanges
            {
                target : albums_library_gridview
                anchors.top: album_library_item.bottom
            }
            AnchorChanges
            {
                target : album_view
                anchors.bottom : album_library_item.bottom
            }
            when : albumView
        }
    ]

    transitions: Transition {
        AnchorAnimation { duration: 250 }
    }

    AlbumDetailView
    {
        id : album_view
        onBackButtonClicked:
        {
            album_library_item.albumView = false
        }
        anchors
        {
            left : parent.left
            right : parent.right
            top : parent.top
            topMargin : 5
            bottomMargin : 5
        }
    }

    GridView
    {
        id : albums_library_gridview
        anchors
        {
            left : parent.left
            right : parent.right
            bottom : parent.bottom
        }
        cellWidth : width / 5
        cellHeight : cellWidth
        model : XBMCPlugin.getAlbumsLibrary();
        clip : true
        delegate : LibraryGridViewDelegate {
            width : albums_library_gridview.cellWidth
            height :albums_library_gridview.cellHeight
            thumbnail: (model.thumbnail !== "") ? XBMCPlugin.getXBMCImageProviderUrl(model.thumbnail) : "empty_cd.png"
            title : model.albumTitle
            onClicked:
            {
                album_view.albumTitle = model.albumTitle + " (" + model.albumYear +")"
                album_view.thumbnail = thumbnail
                album_view.albumSummary = model.description
                album_view.songModel = albums_library_gridview.model.subModelFromId(model.albumId)
                albumView = true;
            }
        }
    }
}

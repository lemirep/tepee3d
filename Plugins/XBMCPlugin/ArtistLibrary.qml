import QtQuick 2.1
import QtGraphicalEffects 1.0

Item
{
    id : artists_library_item
    property  bool artistView : false
    anchors.fill: parent

    states : [
        State
        {
            name : "library_view"
            AnchorChanges
            {
                target : artists_library_gridview
                anchors.top: artists_library_item.top
            }
            AnchorChanges
            {
                target : artist_view
                anchors.bottom : artists_library_item.top
            }
            when : !artistView
        },
        State
        {
            name : "artist_view"
            AnchorChanges
            {
                target : artists_library_gridview
                anchors.top: artists_library_item.bottom
            }
            AnchorChanges
            {
                target : artist_view
                anchors.bottom : artists_library_item.bottom
            }
            when : artistView
        }
    ]

    transitions: Transition {
        AnchorAnimation { duration: 250 }
    }

    ArtistAlbumsView
    {
        id : artist_view
        onBackButtonClicked: artists_library_item.artistView = false
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
        id : artists_library_gridview
        anchors
        {
            left : parent.left
            right : parent.right
            bottom : parent.bottom
        }
        clip : true
        cellWidth : width / 5
        cellHeight : cellWidth
        model : xbmc_plugin.getArtistsLibrary();
        delegate : LibraryGridViewDelegate {
            width : artists_library_gridview.cellWidth
            height :artists_library_gridview.cellHeight
            thumbnail: (model.thumbnail !== "") ? xbmc_plugin.getXBMCImageProviderUrl(model.thumbnail) : "empty_cd.png"
            title : model.artistName
            onClicked:
            {
                artist_view.artistId = model.artistId
                artist_view.thumbnail = thumbnail
                artist_view.artistName = model.artistName
                artist_view.artistAlbumsModel = artists_library_gridview.model.subModelFromId(model.artistId)
                artistView = true;
            }
        }
    }
}

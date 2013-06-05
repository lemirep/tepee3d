import QtQuick 2.0
import QtGraphicalEffects 1.0

GridView
{
    id : artists_library_gridview
    anchors.fill: parent
    cellWidth : width / 5
    cellHeight : cellWidth
    model : XBMCPlugin.getArtistsLibrary();
    delegate : LibraryGridViewDelegate {
        width : artists_library_gridview.cellWidth
        height :artists_library_gridview.cellHeight
        thumbnail: (model.thumbnail !== "") ? XBMCPlugin.getXBMCImageProviderUrl(model.thumbnail) : "empty_cd.png"
        title : model.artistName
    }
}

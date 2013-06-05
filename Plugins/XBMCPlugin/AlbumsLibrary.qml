import QtQuick 2.0

GridView
{
    id : albums_library_gridview
    anchors.fill: parent
    cellWidth : width / 5
    cellHeight : cellWidth
    model : XBMCPlugin.getAlbumsLibrary();
    delegate : LibraryGridViewDelegate {
        width : albums_library_gridview.cellWidth
        height :albums_library_gridview.cellHeight
        thumbnail: (model.thumbnail !== "") ? XBMCPlugin.getXBMCImageProviderUrl(model.thumbnail) : "empty_cd.png"
        title : model.albumTitle
    }
}

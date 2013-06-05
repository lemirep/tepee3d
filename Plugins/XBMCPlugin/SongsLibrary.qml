import QtQuick 2.0

GridView
{
    id : songs_library_gridview
    anchors.fill: parent
    cellWidth : width / 5
    cellHeight : cellWidth
    model : XBMCPlugin.getSongsLibrary();
    delegate : LibraryGridViewDelegate {
        width : songs_library_gridview.cellWidth
        height :songs_library_gridview.cellHeight
        thumbnail: (model.thumbnail !== "") ? XBMCPlugin.getXBMCImageProviderUrl(model.thumbnail) : "empty_cd.png"
        title : model.title
    }
}

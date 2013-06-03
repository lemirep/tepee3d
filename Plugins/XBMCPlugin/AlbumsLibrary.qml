import QtQuick 2.0

GridView
{
    id : albums_library_gridview
    anchors.fill: parent
    cellWidth : width / 5
    cellHeight : height / 2
    model : XBMCPlugin.getAlbumsLibrary();
    delegate : LibraryGridViewDelegate {
        width : albums_library_gridview.cellWidth
        height :albums_library_gridview.cellHeight
        thumbnail: XBMCPlugin.getXBMCImageProviderUrl(model.thumbnail)
        title : model.albumTitle
    }
}

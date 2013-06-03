import QtQuick 2.0

GridView
{
    id : songs_library_gridview
    anchors.fill: parent
    cellWidth : width / 5
    cellHeight : height / 2
    model : XBMCPlugin.getSongsLibrary();
    delegate : LibraryGridViewDelegate {
        width : songs_library_gridview.cellWidth
        height :songs_library_gridview.cellHeight
        thumbnail: XBMCPlugin.getXBMCImageProviderUrl(model.thumbnail)
        title : model.title
    }
}

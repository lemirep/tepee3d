import QtQuick 2.0

GridView
{
    id : shows_library_gridview
    anchors.fill: parent
    cellWidth : width / 5
    cellHeight : height / 2
    model : XBMCPlugin.getTVShowsLibrary();
    delegate : LibraryGridViewDelegate {
        width : shows_library_gridview.cellWidth
        height :shows_library_gridview.cellHeight
        thumbnail: XBMCPlugin.getXBMCImageProviderUrl(model.thumbnail)
        title : model.title
    }
}

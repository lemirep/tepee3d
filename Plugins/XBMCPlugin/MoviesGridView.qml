import QtQuick 2.1

GridView
{
    id : movie_library_gridview
    anchors.fill: parent
    cellWidth : width / 5
    cellHeight : cellWidth
    model : xbmc_plugin.getMoviesLibrary();
    delegate : LibraryGridViewDelegate {
        width : movie_library_gridview.cellWidth
        height :movie_library_gridview.cellHeight
        thumbnail: (model.thumbnail !== "") ? xbmc_plugin.getXBMCImageProviderUrl(model.thumbnail) : "empty_cd.png"
        title : model.title
        onClicked:
        {
            movie_flow_listview.currentMovieIdx = index;
            movie_flow_loader.moveToDetailView()
        }
    }
}

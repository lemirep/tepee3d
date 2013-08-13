import QtQuick 2.1

GridView
{
    id : movie_library_gridview
    anchors.fill: parent
    cellWidth : width / 5
    cellHeight : cellWidth
    model : XBMCPlugin.getMoviesLibrary();
    delegate : LibraryGridViewDelegate {
        width : movie_library_gridview.cellWidth
        height :movie_library_gridview.cellHeight
        thumbnail: (model.thumbnail !== "") ? XBMCPlugin.getXBMCImageProviderUrl(model.thumbnail) : "empty_cd.png"
        title : model.title
        onClicked:
        {
            movie_flow_listview.currentMovieIdx = index;
            movie_flow_loader.moveToDetailView()
        }
    }
}

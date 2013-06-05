import QtQuick 2.0


ListView
{
    id : movie_flow_listview
    property int currentMovieIdx;

    ListModel
    {
        id : movie_flow_model
        ListElement
        {
            source : "MovieDetailView.qml";
        }
        ListElement
        {
            source : "MoviesGridView.qml"
        }
    }

    Component.onCompleted: movie_flow_listview.currentIndex = 1
    anchors.fill: parent
    orientation: ListView.Vertical
    model : movie_flow_model
    interactive: false

    delegate: Component {
        Loader
        {
            id : movie_flow_loader

            opacity : (movie_flow_listview.currentIndex === index) ? 1 : 0
            Behavior on opacity {NumberAnimation {duration : 750}}

            width : movie_flow_listview.width
            height : movie_flow_listview.height
            source : model.source

            function moveToDetailView() {movie_flow_listview.currentIndex = 0;}
            function moveToGridView() {movie_flow_listview.currentIndex = 1}
        }
    }
}

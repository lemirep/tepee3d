import QtQuick 2.0

Item
{
    id : serie_season_delegate

    property int season;
    property string img_src : ""
    property real rotAngle : PathView.onPath ? PathView.delAngle : 0
    property bool isCurrentItem : PathView.isCurrentItem

    z : PathView.onPath ? PathView.delZ : 0
    scale : PathView.onPath ? PathView.delScale : 0
    transform : Rotation { origin.x: 0; origin.y: 0; axis { x: 0; y: 1; z: 0 } angle: rotAngle}

    Behavior on scale {NumberAnimation { duration: 750; easing.type: Easing.OutElastic }}

    onIsCurrentItemChanged:
    {
        if (isCurrentItem)
        {
            if (!rotate_cube.running)
                rotate_cube.restart()
            if (show_pathview_container.currentIndex != -1)
                episodes_pathview_container.model = SeriesPlugin.getEpisodesFromSeasonAndShowId(SeriesPlugin.getFollowedSeriesModel().get(show_pathview_container.currentIndex).serieTvdbId, season)
        }
    }

    Rectangle
    {
        width : serie_season_delegate_pic.width
        height : serie_season_delegate_pic.height
        anchors
        {
            left : serie_season_delegate_pic.left
            top : serie_season_delegate_pic.top
            leftMargin : 4
            topMargin : 4
        }
        color : "black"
        opacity : 0.4
    }

    Image
    {
        id : serie_season_delegate_pic
        source : img_src.replace(".jpg", "-138.jpg")
        fillMode: Image.PreserveAspectFit
        height : parent.height - 10
        asynchronous: true
        cache : true
        anchors
        {
            horizontalCenter : parent.horizontalCenter
            top : parent.top
        }
    }

    Text
    {
        id : season_nbr_text
        color : "white"
        anchors
        {
            left : serie_season_delegate_pic.horizontalCenter
            bottom : serie_season_delegate_pic.top
            bottomMargin : 10
        }
        text : "Season " + season
        font.pointSize: mainWindow.largeFontSize
    }

    MouseArea
    {
        id : serie_season_delegate_ma
        anchors.fill: parent
        onClicked:
        {
            followed_series_season_pathview.currentIndex = index;
            if (isCurrentItem)
            {
                if (show_pathview_container.currentIndex != -1)
                    episodes_pathview_container.model = SeriesPlugin.getEpisodesFromSeasonAndShowId(SeriesPlugin.getFollowedSeriesModel().get(show_pathview_container.currentIndex).serieTvdbId, season)
            }
        }
    }
}

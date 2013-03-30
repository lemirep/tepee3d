import QtQuick 2.0

Item
{
    id : serie_season_delegate

    property string img_src : ""
    property int season;

    scale : serie_season_delegate_ma.pressed ? 0.9 : 1.0
    Behavior on scale {SmoothedAnimation {velocity : 10}}

    Text
    {
        id : season_nbr_text
        color : "white"
        anchors
        {
            horizontalCenter : parent.horizontalCenter
            bottom : parent.bottom
        }
        text : season
    }

    Image
    {
        id : serie_season_delegate_pic
        source : img_src
        fillMode: Image.PreserveAspectFit
        height : parent.height - 10
        asynchronous: true
        anchors
        {
         horizontalCenter : parent.horizontalCenter
         top : parent.top
         bottom : season_nbr_text.top
         bottomMargin : 2
         topMargin : 2
        }
    }

    MouseArea
    {
        id : serie_season_delegate_ma
        anchors.fill: parent
        onClicked:
        {
            cube_effect.texture = img_src
            rotate_cube.restart()
            season_list_view.currentIndex = index;
            episodes_series_listview.model = SeriesPlugin.getEpisodesFromSeasonAndShowId(followed_series_listview.currentItem.serieId, season)
        }
    }
}

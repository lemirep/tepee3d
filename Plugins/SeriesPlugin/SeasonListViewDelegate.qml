import QtQuick 2.0

Item
{
    id : serie_season_delegate

    property string img_src : ""
    property int season;

    scale : serie_season_delegate_ma.pressed ? 0.9 : 1.0
    Behavior on scale {SmoothedAnimation {velocity : 10}}

    Image
    {
        id : serie_season_delegate_pic
        source : img_src
        fillMode: Image.PreserveAspectFit
        height : parent.height - 10
        asynchronous: true
        anchors.centerIn: parent
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

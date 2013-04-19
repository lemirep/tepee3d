import QtQuick 2.0
import QtGraphicalEffects 1.0

Item
{
    id : followed_serie_delegate

    property int serieId : -1;
    property string img_src : ""
    property string series_name : ""
    property string serie_overview;
    property string serie_year;
    property string serie_network;
    property string serie_air_day;
    property string serie_air_time;
    property bool serie_on_sickbeard;
    property date serie_last_update;
    property real rotAngle : PathView.onPath ? PathView.delAngle : 0
    property bool isCurrentItem : PathView.isCurrentItem
    property real reflection : PathView.onPath ? PathView.delReflect : 0

    //    scale : followed_series_delegate_ma.pressed ? 0.9 : 1.0
    z : PathView.onPath ? PathView.delZ : 0
    scale : PathView.onPath ? PathView.delScale : 0
    transform : Rotation { origin.x: 0; origin.y: 0; axis { x: 0; y: 1; z: 0 } angle: rotAngle}


    onIsCurrentItemChanged:
    {
        if (isCurrentItem)
        {
            serie_detailed_view.serie_id = serieId;
            serie_detailed_view.serie_air_day = serie_air_day;
            serie_detailed_view.serie_air_time = serie_air_time;
            serie_detailed_view.serie_network = serie_network
            serie_detailed_view.serie_overview = serie_overview
            serie_detailed_view.serie_last_update = "Last Update on the : " + serie_last_update.getDate() + "/" + (serie_last_update.getMonth() + 1) + "/" + serie_last_update.getFullYear()
            serie_detailed_view.serie_year = serie_year
            serie_detailed_view.serie_on_sickbeard = serie_on_sickbeard
            if (!rotate_cube.running)
                rotate_cube.restart()
        }
    }

    //    DropShadow
    //    {
    //        anchors.fill: followed_series_delegate_pic
    //        source : followed_series_delegate_pic
    //        radius : 8
    //        samples: 16
    //        horizontalOffset: 5
    //        verticalOffset: 5
    //        opacity: 0.5
    //        fast : true
    //    }
    Rectangle
    {
        width : followed_series_delegate_pic.width
        height : followed_series_delegate_pic.height
        anchors
        {
            top : followed_series_delegate_pic.top
            left : followed_series_delegate_pic.left
            leftMargin : 8
            topMargin : 8
        }
        radius : 2
        color : "#44000000"
    }
    Image
    {
        id : followed_series_delegate_pic
        fillMode: Image.PreserveAspectFit
        height : parent.height - 10
        cache : true
        anchors
        {
            right : parent.right
            verticalCenter : parent.verticalCenter
            margins : 10
        }
        asynchronous : true
        source : img_src.replace(".jpg", "-300.jpg")
    }


    MouseArea
    {
        id : followed_series_delegate_ma
        anchors.fill : followed_series_delegate_pic
        onClicked:
        {
            if (isCurrentItem)
            {
                console.log("serieId " + serieId)
                followed_series_view.state = "seasons_shows_view"
                season_pathview_container.model = SeriesPlugin.getSeasonsModelFromSerieId(serieId)
                episodes_pathview_container.model = null;
            }
            else
                followed_series_pathview.currentIndex = index;
        }
    }
}

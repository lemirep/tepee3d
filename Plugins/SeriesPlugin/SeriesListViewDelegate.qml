import QtQuick 2.0
import QtGraphicalEffects 1.0

Item
{
    id : followed_serie_delegate

    property int serieId : -1;
    property string img_src : ""
    property string series_name : ""
    property string slug : ""
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
            serie_detailed_view.serie_title = series_name;
            serie_detailed_view.serie_slug = slug;
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

    ReflectedImage
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
        reflectRatio : 0.06
        reflectOpacity : 0.3
        Image
        {
            id : shadow
    //        fillMode: Image.PreserveAspectFit
            width : parent.width + 40
            y : followed_series_delegate_pic.y
            anchors
            {
                right : followed_series_delegate_pic.right
                top : parent.bottom
                topMargin : -40
                rightMargin : -20
            }
            source : "halo.png"
            asynchronous : true

        }
    }



//    ReflectedImage
//    {
//        id : followed_series_delegate_pic
//        fillMode: Image.PreserveAspectFit
//        height : parent.height - 10
//        cache : true
//        anchors
//        {
//            right : parent.right
//            //            left : parent.left
//            verticalCenter : parent.verticalCenter
//            margins : 10
//        }
//        asynchronous : true
//        reflectRatio : reflection
//        source : img_src.replace(".jpg", "-300.jpg")
//    }


    //    DropShadow {
    //            anchors.fill: followed_series_delegate_pic
    //            horizontalOffset: 3
    //            verticalOffset: 3
    //            radius: 8.0
    //            samples: 16
    //            color: "grey"
    //            source: followed_series_delegate_pic
    //        }


//    Text
//    {
//        id : followed_series_delegate_text
//        anchors
//        {
//            right : followed_series_delegate_pic.horizontalCenter
//            top : followed_series_delegate_pic.bottom
//            topMargin : 10
//        }
//        color : "white"
////        text : series_name
//        font.pointSize: 14
//    }

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

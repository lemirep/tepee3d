import QtQuick 2.0

Item
{
     id : show_pathview_container
     property alias model : followed_series_pathview.model
     property alias currentIndex : followed_series_pathview.currentIndex

     PathView
     {
         id : followed_series_pathview
         smooth : true
         anchors.fill : parent
         focus : true
         model : SeriesPlugin.getFollowedSeriesModel();
         flickDeceleration : 200
         pathItemCount : 8
         path : Path {
             startX : mainWindow.width / 3
             startY : mainWindow.height / 2
             PathAttribute {name : "delScale"; value : 1}
             PathAttribute {name : "delZ"; value : 1}
             PathAttribute {name : "delAngle"; value : 5}
             PathCurve { x: mainWindow.width / 6; y: mainWindow.height / 3;}
             PathAttribute {name : "delScale"; value : 0.7}
             PathAttribute {name : "delZ"; value : 0.5}
             PathAttribute {name : "delAngle"; value : 30}
             PathCurve { x: 0; y: mainWindow.height / 2;}
             PathAttribute {name : "delScale"; value : 0.5}
             PathAttribute {name : "delZ"; value : 0}
             PathAttribute {name : "delAngle"; value : 60}
         }
         delegate : SeriesListViewDelegate {
             serieId : model.serieTvdbId
             slug : model.slug
             img_src : model.imageUrl
             series_name: model.serieName
             serie_overview: model.serieOverview
             serie_year : model.serieYear
             serie_network : model.serieNetwork
             serie_last_update: model.serieLastUpdate
             serie_air_day: model.serieAirDay
             serie_air_time: model.serieAirTime
             width : 400
             height : 400
         }
     }
}

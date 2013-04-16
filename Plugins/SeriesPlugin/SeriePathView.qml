import QtQuick 2.0

Item
{
     id : show_pathview_container
     property alias model : followed_series_pathview.model
     property alias currentIndex : followed_series_pathview.currentIndex
     property alias currentItem : followed_series_pathview.currentItem

     PathView
     {
         id : followed_series_pathview
         smooth : true
         anchors.fill : parent
         focus : true
         model : SeriesPlugin.getFollowedSeriesModel();
         flickDeceleration : 200
         pathItemCount : 8
         cacheItemCount : 8
         path : Path {
             startX : mainWindow.width / 3
             startY : mainWindow.height / 2
             PathAttribute {name : "delScale"; value : 1}
             PathAttribute {name : "delZ"; value : 1}
             PathAttribute {name : "delAngle"; value : 5}
             PathAttribute {name : "delReflect"; value : 0.3}
             PathCurve { x: mainWindow.width / 6; y: mainWindow.height / 3;}
             PathAttribute {name : "delScale"; value : 0.7}
             PathAttribute {name : "delZ"; value : 0.7}
             PathAttribute {name : "delAngle"; value : 30}
             PathAttribute {name : "delReflect"; value : 0.05}
             PathCurve { x: 0; y: mainWindow.height / 2;}
             PathAttribute {name : "delScale"; value : 0.4}
             PathAttribute {name : "delZ"; value : 0}
             PathAttribute {name : "delAngle"; value : 60}
             PathAttribute {name : "delReflect"; value : 0}
         }
         delegate : SeriesListViewDelegate {
             serieId : model.serieTvdbId
             img_src : model.imageUrl
             series_name: model.serieName
             serie_overview: model.serieOverview
             serie_year : model.serieYear
             serie_network : model.serieNetwork
             serie_last_update: model.serieLastUpdate
             serie_air_day: model.serieAirDay
             serie_air_time: model.serieAirTime
             serie_on_sickbeard: model.serieOnSickbeard
             width : 400
             height : 400
         }
     }
     Text
     {
         id : episode_title
         style: Text.Outline
         styleColor: "#440033cc"
         color : "White"
         width: mainWindow.width / 3
         visible : (followed_series_pathview.pathItemCount > 0)
         wrapMode: Text.WrapAtWordBoundaryOrAnywhere
         horizontalAlignment: Text.AlignHCenter
         anchors
         {
             horizontalCenter: parent.horizontalCenter
             bottom : parent.bottom
             bottomMargin : mainWindow.height / 5
         }
         text : (followed_series_pathview.currentItem) ? show_pathview_container.currentItem.series_name : ""
         font.pointSize: 24
     }
}

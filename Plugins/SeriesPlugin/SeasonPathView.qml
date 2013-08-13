import QtQuick 2.1

Item
{
    id : season_pathview_container
    property alias model : followed_series_season_pathview.model
    property alias currentItem : followed_series_season_pathview.currentItem

    states : [State    {PropertyChanges {target: season_path; x_target : mainWindow.width / 6} when : !seriesplugin_item.consultingEpisode},
              State    {PropertyChanges {target: season_path; x_target : 0} when : seriesplugin_item.consultingEpisode}]
    transitions: Transition {SmoothedAnimation {target : season_path; properties : "x_target"; duration : 750; velocity : 10}}

    PathView
    {
        id : followed_series_season_pathview
        smooth : true
        anchors.fill : parent
        focus : true
        flickDeceleration : 200
        pathItemCount : 10
        preferredHighlightBegin: 0.50
        preferredHighlightEnd : 0.55
        path : Path {
            id : season_path
            property real x_target : mainWindow.width / 6
            startX : 0
            startY : 0
            PathPercent {value : 0}
            PathAttribute {name : "delZ"; value : 0.5}
            PathAttribute {name : "delScale"; value : 0.4}
            PathAttribute {name : "delAngle"; value : 30}
            // CENTER
            PathLine { x: season_path.x_target; y: height / 2;}
            PathPercent {value : 0.5}
            PathAttribute {name : "delScale"; value : 1}
            PathAttribute {name : "delZ"; value : 1}
            PathAttribute {name : "delAngle"; value : 0}
            // BOTTOM
            PathLine { x: 0; y: mainWindow.height;}
            PathPercent {value : 1}
            PathAttribute {name : "delZ"; value : 0.5}
            PathAttribute {name : "delScale"; value : 0.4}
            PathAttribute {name : "delAngle"; value : 30}
        }
        delegate : SeasonPathViewDelegate {
            img_src : model.imageUrl
            season : model.seasonId
            width : 200
            height : 200
        }
    }
}

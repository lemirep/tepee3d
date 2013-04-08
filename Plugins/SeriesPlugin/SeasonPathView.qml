import QtQuick 2.0

Item
{
    id : season_pathview_container
    property alias model : followed_series_season_pathview.model

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
        path : Path {
            id : season_path
            property real x_target : mainWindow.width / 6
            startX : x_target
            startY : mainWindow.height / 2
            PathAttribute {name : "delScale"; value : 1}
            PathAttribute {name : "delZ"; value : 1}
            PathAttribute {name : "delAngle"; value : 0}
            // TOP
            PathCurve { x: 0; y: 0;}
            PathAttribute {name : "delZ"; value : 0.5}
            PathAttribute {name : "delScale"; value : 0.4}
            PathAttribute {name : "delAngle"; value : 30}
            // BETWEEN TOP AND BOTTOM
            PathCurve { x: -100; y: mainWindow.height / 2;}
            PathAttribute {name : "delZ"; value : 0.5}
            PathAttribute {name : "delScale"; value : 0.3}
            PathAttribute {name : "delAngle"; value : 60}
            // BOTTOM
            PathCurve { x: 0; y: mainWindow.height;}
            PathAttribute {name : "delZ"; value : 0.5}
            PathAttribute {name : "delScale"; value : 0.4}
            PathAttribute {name : "delAngle"; value : 30}
            // BACK TO START
            PathCurve { x: season_path.startX; y: mainWindow.height / 2}
            PathAttribute {name : "delScale"; value : 1}
            PathAttribute {name : "delAngle"; value : 0}
            PathAttribute {name : "delZ"; value : 0.5}
        }
        delegate : SeasonListViewDelegate {
            img_src : model.imageUrl
            season : model.seasonId
            width : 200
            height : 200
        }
    }
}

import QtQuick 2.0

Item
{
    id : episodes_pathview_container
    property alias model : followed_series_episodes_pathview.model

    states : [State    {PropertyChanges {target: episode_path; x_target : followed_series_episodes_pathview.width / 2} when : !seriesplugin_item.consultingEpisode},
              State    {PropertyChanges {target: episode_path; x_target : followed_series_episodes_pathview.width} when : seriesplugin_item.consultingEpisode}]
    transitions: Transition {SmoothedAnimation {target : episode_path; properties : "x_target"; duration : 750; velocity : 10}}

    PathView
    {
        id : followed_series_episodes_pathview
        smooth : true
        anchors.fill : parent
        focus : true
        flickDeceleration : 200
        path :  Path {
            id : episode_path
            property real x_target : width / 2
            startX : x_target
            startY : mainWindow.height / 2
            PathAttribute {name : "delScale"; value : 1}
            PathAttribute {name : "delZ"; value : 1}
            PathAttribute {name : "delAngle"; value : 0}
            PathAttribute {name : "delOpacity"; value : 1}
            // TOP
            PathCurve { x: width; y: 0}
            PathAttribute {name : "delScale"; value : 0.5}
            PathAttribute {name : "delZ"; value : 0.5}
            PathAttribute {name : "delAngle"; value : -60}
            PathAttribute {name : "delOpacity"; value : 0.7}
            // BETWEEN TOP AND BOTTOM
            PathCurve { x: 3 * width / 2; y: mainWindow.height / 2}
            PathAttribute {name : "delScale"; value : 0.3}
            PathAttribute {name : "delZ"; value : 0.4}
            PathAttribute {name : "delAngle"; value : -120}
            PathAttribute {name : "delOpacity"; value : 0.3}
            // BOTTOM
            PathCurve { x: width; y: mainWindow.height}
            PathAttribute {name : "delScale"; value : 0.5}
            PathAttribute {name : "delZ"; value : 0.5}
            PathAttribute {name : "delAngle"; value : -60}
            PathAttribute {name : "delOpacity"; value : 0.7}
            // BACK TO START
            PathCurve { x: episode_path.startX; y: mainWindow.height / 2}
            PathAttribute {name : "delScale"; value : 1}
            PathAttribute {name : "delZ"; value : 1}
            PathAttribute {name : "delAngle"; value : 0}
            PathAttribute {name : "delOpacity"; value : 1}
        }
        delegate : EpisodeListViewDelegate   {
            episodeNumber : model.episodeNumber
            episodeTitle : model.episodeTitle
            episodeOverview : model.episodeSummary
            episodeAiring : model.episodeAiring
            img_src : model.imageUrl
            width : mainWindow.width / 4
            height : mainWindow.height / 4
        }
    }
}

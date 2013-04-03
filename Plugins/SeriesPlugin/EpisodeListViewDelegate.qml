import QtQuick 2.0

Item
{
    id : episode_delegate_item

    property int episodeNumber
    property date episodeAiring
    property string episodeTitle
    property string episodeOverview
    property string img_src

    scale : episode_delegate_ma.pressed ? 0.9 : 1

    Behavior on scale {SmoothedAnimation {velocity : 10}}

    Image
    {
        id : episode_delegate_pic
        fillMode : Image.PreserveAspectFit
        asynchronous : true
        height : parent.height - 10
        anchors
        {
            left : parent.left
            verticalCenter : parent.verticalCenter
            leftMargin : 10
        }
        source : img_src
    }

    Rectangle
    {
        anchors.fill: episode_delegate_nbr_text
        anchors.margins: -2
        border
        {
            width : 1
            color : "white"
        }
        radius : 2
        color : "#0066CC"
        opacity : 0.3
        smooth : true
    }
    Text
    {
        id : episode_delegate_nbr_text
        anchors
        {
            top : parent.top
            right : parent.right
            margins : 2
        }
        color : "white"
        text : episodeNumber
    }

    Text
    {
        id : episode_delegate_text
        anchors
        {
            left : episode_delegate_pic.right
            right : parent.right
            verticalCenter : parent.verticalCenter
            rightMargin : 10
            leftMargin : 10
        }
        color : "white"
        text : episodeTitle
    }

    Text
    {
        id : episode_delegate__airing_text
        anchors
        {
            right : parent.right
            bottom : parent.bottom
            rightMargin : 2
            bottomMargin : 2
        }
        color : "white"
        text : episodeAiring.getHours() + ":"
               + ((episodeAiring.getMinutes() < 10) ? ("0" + episodeAiring.getMinutes()) : episodeAiring.getMinutes())
               + "-" + episodeAiring.getDate()
               + "/" + episodeAiring.getMonth()
               + "/" + episodeAiring.getFullYear()
    }

    MouseArea
    {
        id : episode_delegate_ma
        anchors.fill: parent

        onClicked:
        {
            cube_effect.texture = img_src
            cube_anim_article.restart()
            detailed_episode_view.title = episodeTitle
            detailed_episode_view.summary = episodeOverview
            detailed_episode_view.isShown = true
//            seriesplugin_item.consultingEpisode = true;
//            rotate_cube.restart()
        }
    }
}

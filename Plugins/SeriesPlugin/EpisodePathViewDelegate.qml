import QtQuick 2.0

Item
{
    id : episode_delegate_item

    property int episodeId
    property int episodeNumber
    property date episodeAiring
    property string episodeTitle
    property string episodeOverview
    property string img_src
    property string episodeSickbeardStatus
    property bool   episodeSeen

    property real rotAngle : PathView.onPath ? PathView.delAngle : 0
    property bool isCurrentItem : PathView.isCurrentItem
    property real scaleValue : PathView.onPath ? PathView.delScale : 0

    z : PathView.onPath ? PathView.delZ : 0
    scale : episode_delegate_ma.pressed ? (scaleValue - 0.1) : scaleValue
    opacity :PathView.onPath ? PathView.delOpacity : 0
    Behavior on scale {NumberAnimation { duration: 750; easing.type: Easing.OutElastic }}

    onIsCurrentItemChanged: {if (isCurrentItem && !rotate_cube.running)rotate_cube.restart()}

    transform: [Rotation { origin.x: 0; origin.y: 0; axis { x: 0; y: 1; z: 0 } angle: rotAngle}]

    Image
    {
        id : show_pic
        fillMode: Image.PreserveAspectFit
        source : (show_pathview_item.currentItem) ? show_pathview_item.currentItem.img_src.replace(".jpg", "-300.jpg") : "";
        width: 180
        opacity : 0.9
    }
    Image
    {
        id: dvd_cover
        source: "dvdbox.png"
        anchors
        {
            left : show_pic.left
            leftMargin : -23
            right : show_pic.right
            rightMargin : -5
            top : show_pic.top
            topMargin : -4
            bottom : show_pic.bottom
            bottomMargin : -6
        }
    }

    Text
    {
        id : episode_delegate_nbr_text
        anchors
        {
            bottom : show_pic.bottom
            left : show_pic.left
            margins : 4
        }
        color : "white"
        text : episodeNumber
        font.pointSize: mainWindow.largeFontSize
        style: Text.Outline
        styleColor: "#cc9900"
    }

    Text
    {
        id : episode_delegate_text
        clip : true
        elide: Text.ElideRight
        width : dvd_cover.width - 20
        anchors.centerIn : dvd_cover
        color : "white"
        text : episodeTitle
        font.pixelSize: mainWindow.largeFontSize
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        horizontalAlignment: Text.AlignHCenter
        style: Text.Outline
        styleColor: "#cc9900"
    }

    Text
    {
        id : episode_delegate__airing_text
        anchors
        {
            left : show_pic.left
            top : show_pic.top
            margins : 2
        }
        color : "white"
        text : episodeAiring.getDate()
               + "/" + (episodeAiring.getMonth() + 1)
               + "/" + episodeAiring.getFullYear()
        font.pixelSize: mainWindow.smallFontSize
    }

    Item
    {
        visible : (show_pathview_item.currentItem) ? show_pathview_item.currentItem.serie_on_sickbeard : false
        anchors
        {
            top : dvd_cover.top
            right : dvd_cover.right
        }

        Image
        {
            id : sickbeard
            source : "sickbeard_logo.png"
            width : 20
            fillMode: Image.PreserveAspectFit
            anchors
            {
                top : parent.top
                right : parent.right
                rightMargin : 8
                topMargin : 4
            }
        }
        Text
        {
            id : sickbeard_status
            text : episodeSickbeardStatus
            anchors
            {
                right : sickbeard.left
                top : sickbeard.top
                margins : 2
            }
            color : "white"
            font.pixelSize: mainWindow.smallFontSize
            style: Text.Outline
            styleColor: "#cc9900"
        }
    }

    OkButton
    {
        id : seen
        width : 20
        visible : episodeSeen
        anchors
        {
            bottom :dvd_cover.bottom
            right : dvd_cover.right
            rightMargin : 10
            bottomMargin : -5
        }
    }

    MouseArea
    {
        id : episode_delegate_ma
        anchors.fill: dvd_cover
        onClicked:
        {
            followed_series_episodes_pathview.currentIndex = index;
            if (isCurrentItem)
            {
                seriesplugin_item.consultingEpisode = true
                detailed_episode_view.title = currentItem.episodeTitle
                detailed_episode_view.summary = currentItem.episodeOverview
                detailed_episode_view.image_src = currentItem.img_src.replace(".jpg", "-218.jpg")
                detailed_episode_view.serieSickBeard = show_pathview_item.currentItem.serie_on_sickbeard
            }
        }
        onPressAndHold:
        {
            SeriesPlugin.markEpisodeAsSeen(show_pathview_item.currentItem.serieId, season_pathview_container.currentItem.season, episodeId, !episodeSeen)
        }
    }
}

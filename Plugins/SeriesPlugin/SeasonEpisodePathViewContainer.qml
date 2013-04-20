import QtQuick 2.0

Item
{
    id : season_episode_item
    property alias seasonModel : season_pathview_container.model
    property alias episodeModel : episodes_pathview_container.model

    SeasonPathView
    {
        id : season_pathview_container
        anchors
        {
            left : parent.left
            right : parent.horizontalCenter
            top : parent.top
            bottom : parent.bottom
        }
    }


    EpisodePathView
    {
        id : episodes_pathview_container
        anchors
        {
            left : parent.horizontalCenter
            right : parent.right
            top : parent.top
            bottom : parent.bottom
        }
    }

    Item
    {
        id : tool_bar_episodes
        enabled : (opacity === 1)
        opacity : (consultingEpisode) ? 0 : 1
        Behavior on opacity {NumberAnimation {duration : 500}}
        width : 180
        height : 60
        anchors
        {
            horizontalCenter : parent.horizontalCenter
            top : parent.verticalCenter
            topMargin : parent.width / 6
        }
        Rectangle
        {
            color : "grey"
            opacity : 0.4
            radius : 5
            anchors.fill: parent
            border
            {
                width : 1
                color : "white"
            }
        }

        BackButton
        {
            id : back_episode_button
            anchors
            {
                bottom : parent.bottom
                horizontalCenter : parent.horizontalCenter
                leftMargin : 2
            }
            onClicked : {followed_series_view.state = "shows_view";}
        }

        Image
        {
            id : check_all_episode_season_button
            height : 50
            width : 50
            scale : check_all_button_ma.pressed ? 0.9 : 1
            source : "check_all.png"
            fillMode: Image.PreserveAspectFit
            MouseArea
            {
                id : check_all_button_ma
                anchors.fill: parent
                onClicked: {SeriesPlugin.markSeasonAsSeen(show_pathview_item.currentItem.serieId, season_pathview_container.currentItem.season)}
            }
            anchors
            {
                verticalCenter : parent.verticalCenter
                right : parent.right
                rightMargin : 5
            }
        }

    }

    DetailedEpisodeView
    {
        id : detailed_episode_view
        enabled : (opacity === 1)
        opacity : (consultingEpisode) ? 1 : 0

        anchors
        {
            fill : parent
            leftMargin : mainWindow.width / 4
            rightMargin : mainWindow.width / 4
            topMargin : mainWindow.height / 8
            bottomMargin : mainWindow.height / 8
        }
    }
}

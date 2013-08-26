import QtQuick 2.1
import Qt3D 2.0
import Qt3D.Shapes 2.0

Item3D
{
    id : seriesplugin_item

    position : Qt.vector3d(0, 0, 0)

    property bool isFocused : false;
    property bool consultingEpisode : false
    property bool synchingWeb : series_plugin.synchingWebServices

    // HAS TO BE IMPLEMENTED
    function roomEntered()    {}
    // HAS TO BE IMPLEMENTED
    function roomLeft()    {}
    // HAS TO BE IMPLEMENTED
    function switchToIdleFocusView()    {plugin_base.moveCamera(); isFocused = false}
    // HAS TO BE IMPLEMENTED
    function switchToSelectedFocusView()    {isFocused = false}
    // HAS TO BE IMPLEMENTED
    function switchToFocusedView()
    {
        var eyePos = plugin_base.getRoomPosition();
        eyePos.z += (-10)

        var widgetPos = plugin_base.getRoomPosition();
        widgetPos.x += plugin_base.pluginPosition.x
        widgetPos.y += plugin_base.pluginPosition.y
        widgetPos.z += plugin_base.pluginPosition.z
        var up = Qt.vector3d(0, 1, 0)
        console.log("POSITION ------> P" + plugin_base.pluginPosition + " R " + plugin_base.getRoomPosition() + " W " + widgetPos)
        plugin_base.moveCamera(eyePos, widgetPos, up);
        isFocused = true;
        followed_series_view.state = "shows_view"
    }

    Cube
    {
        id : cube_picture
        scale : 3
        effect : cube_effect
        transform : [Rotation3D {id : cube_x_rotate; axis : Qt.vector3d(0, 0, 1); angle : -90},
            Rotation3D {id : cube_y_rotate;axis : Qt.vector3d(0, 1, 0); angle : 45}]
        onClicked : {plugin_base.askForFocusedFocusState()}
    }

    ParallelAnimation
    {
        id : cube_anim_article
        SmoothedAnimation
        {
            target : cube_picture
            property : "scale"
            duration : 1000
            to : 0
            velocity : 1
        }
        SmoothedAnimation
        {
            target : cube_y_rotate
            duration : 750
            property : "angle"
            to : cube_y_rotate.angle >= 360 ? 0 : 360
        }
    }

    ParallelAnimation
    {
        id : cube_anim_article_close
        loops: 1
        SmoothedAnimation
        {
            target : cube_picture
            property : "scale"
            duration : 1000
            to : 5
            velocity : 1
        }
        SmoothedAnimation
        {
            target : cube_y_rotate
            duration : 750
            property : "angle"
            to : cube_y_rotate.angle >= 360 ? 0 : 360
        }
    }

    SequentialAnimation
    {
        id : loading_animation
        running: synchingWeb
        loops : Animation.Infinite
        SmoothedAnimation
        {
            target : cube_picture
            property : "scale"
            duration : 750
            to : 1
            velocity : 1
        }
        SmoothedAnimation
        {
            target : cube_picture
            property : "scale"
            duration : 750
            to : 3
            velocity : 1
        }
    }
    ParallelAnimation
    {
        id : rotate_cube
        SmoothedAnimation
        {
            target : cube_x_rotate
            duration : 750
            property : "angle"
            to : cube_x_rotate.angle >= 270 ? -90 : 270
        }
        SequentialAnimation
        {
            SmoothedAnimation
            {
                target : cube_picture
                property : "scale"
                duration : 375
                to : 1
                velocity : 1
            }
            SmoothedAnimation
            {
                target : cube_picture
                property : "scale"
                duration : 375
                to : 3
                velocity : 1
            }
        }
        SmoothedAnimation
        {
            target : cube_y_rotate
            duration : 750
            property : "angle"
            to : cube_y_rotate.angle >= 360 ? 0 : 360
        }
    }

    Effect
    {
        id : cube_effect
        color : "white"
        useLighting : false
        blending : true
    }

    Item
    {
        id : followed_series_item
        enabled : isFocused
        opacity : isFocused ? 1 : 0
        width : mainWindow.width
        height : mainWindow.height
        state : series_plugin.pluginState

        states : [
            State
            {
                name : "shows_view";
                PropertyChanges {target: followed_series_view; state : "shows_view"}
                PropertyChanges {target : followed_series_view; opacity : 1}
                PropertyChanges {target : sickbeard_config; opacity : 0}
                PropertyChanges {target : search_bar_container; opacity : 0}
                PropertyChanges {target: show_planning_view_item; opacity : 0}
            },
            State
            {
                name : "seasons_shows_view";
                PropertyChanges {target: followed_series_view; state: "seasons_shows_view"}
                PropertyChanges {target : followed_series_view; opacity : 1}
                PropertyChanges {target : sickbeard_config; opacity : 0}
                PropertyChanges {target : search_bar_container; opacity : 0}
                PropertyChanges {target : show_planning_view_item; opacity : 0}
            },
            State
            {
                name : "search_shows";
                PropertyChanges {target : followed_series_view; opacity : 0}
                PropertyChanges {target: followed_series_view; state : "shows_view"}
                PropertyChanges {target : sickbeard_config; opacity : 0}
                PropertyChanges {target : search_bar_container; opacity : 1}
                PropertyChanges {target : show_planning_view_item; opacity : 0}
            },
            State
            {
                name : "configure_sickbeard";
                PropertyChanges {target: followed_series_view; state : "shows_view"}
                PropertyChanges {target : followed_series_view; opacity : 0}
                PropertyChanges {target : sickbeard_config; opacity : 1}
                PropertyChanges {target : search_bar_container; opacity : 0}
                PropertyChanges {target : show_planning_view_item; opacity : 0}
            },
            State
            {
                name : "show_planning_view"
                PropertyChanges {target : show_planning_view_item; opacity : 1}
                PropertyChanges {target : followed_series_view; state : "shows_view"}
                PropertyChanges {target : followed_series_view; opacity : 0}
                PropertyChanges {target : sickbeard_config; opacity : 0}
                PropertyChanges {target : search_bar_container; opacity : 0}
            }
        ]

        transitions: [
            Transition {
                NumberAnimation {target : followed_series_view; property: "opacity"; duration: 750; easing.type: Easing.InOutQuad }
                NumberAnimation {target : sickbeard_config; property: "opacity"; duration: 750; easing.type: Easing.InOutQuad }
                NumberAnimation {target : search_bar_container; property: "opacity"; duration: 750; easing.type: Easing.InOutQuad }
            }]

        SearchSerie
        {
            id : search_bar_container
            opacity : 0
            enabled : opacity === 1
            width : parent.width / 3
            anchors
            {
                top : parent.top
                topMargin : 100
                horizontalCenter : parent.horizontalCenter
                bottom : parent.bottom
                bottomMargin : 100
            }
        }

        SickBeardConfig
        {
            id : sickbeard_config
            opacity : 0
            enabled : opacity === 1
            width : parent.width / 3
            anchors
            {
                top : parent.top
                topMargin : 100
                horizontalCenter : parent.horizontalCenter
                bottom : parent.bottom
                bottomMargin : 100
            }
        }

        Item
        {
            id : followed_series_view
            enabled : opacity === 1
            opacity : 0
            anchors.fill: parent

            states :    [
                State
                {
                    name : "shows_view"
                    PropertyChanges {target: show_pathview_item; opacity : 1}
                    PropertyChanges {target: season_episode_item; opacity : 0}
                },
                State
                {
                    name : "seasons_shows_view"
                    PropertyChanges {target: show_pathview_item; opacity : 0}
                    PropertyChanges {target: season_episode_item; opacity : 1}
                }
            ]
            transitions : [Transition {
                    NumberAnimation { target: show_pathview_item; property: "opacity"; duration: 750; easing.type: Easing.InOutQuad }
                    NumberAnimation { target: season_episode_item; property: "opacity"; duration: 750; easing.type: Easing.InOutQuad }
                }]


            SeriePathViewContainer
            {
                id : show_pathview_item
                anchors.fill: parent
                enabled : opacity === 1
            }

            SeasonEpisodePathViewContainer
            {
                id : season_episode_item
                anchors.fill: parent
                enabled : opacity === 1
            }
        }

        ShowPlanningView
        {
            id : show_planning_view_item
            anchors.fill: parent
            enabled : (opacity === 1)
        }
    }
}

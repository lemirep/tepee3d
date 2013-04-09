import QtQuick 2.0

Item
{
    anchors.fill: parent
    state : SeriesPlugin.pluginState

    states : [
        State
        {
            name : "search_shows"
            PropertyChanges {target : adding_show_menu; opacity : 1}
            PropertyChanges {target : normal_menu; opacity : 0}
        },
        State
        {
            name : "shows_view"
            PropertyChanges {target : adding_show_menu; opacity : 0}
            PropertyChanges {target : normal_menu; opacity : 1}
        }

    ]

    transitions: [
    Transition {
        NumberAnimation { target: adding_show_menu; property: "opacity"; duration: 750; easing.type: Easing.InOutQuad }
        NumberAnimation { target: normal_menu; property: "opacity"; duration: 750; easing.type: Easing.InOutQuad }
    }]

    Item
    {
        id : adding_show_menu
        enabled : opacity === 1
        opacity : 0
        anchors.fill: parent
        CloseButton
        {
            id : back_show_button
            anchors
            {
                verticalCenter: parent.verticalCenter
                left: parent.left
                leftMargin : 50
            }
            onClicked : {SeriesPlugin.pluginState = "shows_view"; menuBottomMain.isShown = false}
        }
        Text
        {
            text : "Back"
            font.pointSize: 14
            color : "white"
            anchors
            {
                top : back_show_button.bottom
                topMargin : 25
                horizontalCenter : back_show_button.horizontalCenter
            }
        }
    }

    Row
    {
        id : normal_menu
        enabled : opacity === 1
        anchors.fill: parent
        opacity : 0
        spacing : 15

        Item
        {
            width : add_show_button_text.width
            height : parent.height
            AddButton
            {
                id : add_show_button
                anchors
                {
                    verticalCenter: parent.verticalCenter
                    horizontalCenter : add_show_button_text.horizontalCenter
                }
                onClicked : {SeriesPlugin.pluginState = "search_shows"; menuBottomMain.isShown = false}
            }

            Text
            {
                id : add_show_button_text
                text : "Add a Show"
                font.pointSize: 14
                color : "white"
                anchors
                {
                    top : add_show_button.bottom
                    topMargin : 25
                    horizontalCenter : parent.horizontalCenter

                }
            }
        }

        Item
        {
            width : refresh_show_button_text.width
            height : parent.height
            RefreshButton
            {
                id : refresh_show_button
                anchors
                {
                    verticalCenter: parent.verticalCenter
                    horizontalCenter : refresh_show_button_text.horizontalCenter
                }
                onClicked : {SeriesPlugin.updateFollowedShows(); menuBottomMain.isShown = false}
            }

            Text
            {
                id : refresh_show_button_text
                text : "Refresh Shows"
                font.pointSize: 14
                color : "white"
                anchors
                {
                    top : refresh_show_button.bottom
                    topMargin : 25
                    horizontalCenter : parent.horizontalCenter
                }
            }
        }

        Item
        {
            width : sync_with_sickbeard_text.width
            height : parent.height
            RefreshButton
            {
                id : sync_with_sickbeard_button
                anchors
                {
                    verticalCenter : parent.verticalCenter
                    horizontalCenter : sync_with_sickbeard_text.horizontalCenter
                }
                onClicked : {SeriesPlugin.retrieveSickBeardShows(); menuBottomMain.isShown = false}
            }

            Text
            {
                id : sync_with_sickbeard_text
                text : "Sync with SickBeard"
                font.pointSize: 14
                color : "white"
                anchors
                {
                    top : sync_with_sickbeard_button.bottom
                    topMargin : 25
                    horizontalCenter : parent.horizontalCenter
                }
            }
        }

        Item
        {
            width : set_sickbeard_config_text.width
            height : parent.height
            SettingsButton
            {
                id : set_sickbeard_config
                anchors
                {
                    verticalCenter : parent.verticalCenter
                    horizontalCenter : set_sickbeard_config_text.horizontalCenter
                }
                onClicked : {SeriesPlugin.pluginState = "configure_sickbeard"; menuBottomMain.isShown = false}
            }
            Text
            {
                id : set_sickbeard_config_text
                text : "Configure SickBeard"
                font.pointSize: 14
                color : "white"
                anchors
                {
                    top : set_sickbeard_config.bottom
                    topMargin : 25
                    horizontalCenter : parent.horizontalCenter
                }
            }
        }
    }
}


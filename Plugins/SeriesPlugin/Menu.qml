import QtQuick 2.0

Item
{
    anchors.fill: parent
    property bool addShow : SeriesPlugin.addShow

    Item
    {
        id : adding_show_menu
        enabled : opacity === 1
        opacity : (addShow) ? 1 : 0
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
            onClicked : {SeriesPlugin.addShow = false; menuBottomMain.isShown = false}
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

    Item
    {
        id : normal_menu
        enabled : opacity === 1
        anchors.fill: parent
        opacity : (addShow) ? 0 : 1

        AddButton
        {
            id : add_show_button
            anchors
            {
                verticalCenter: parent.verticalCenter
                horizontalCenter : add_show_button_text.horizontalCenter
            }
            onClicked : {SeriesPlugin.addShow = true; menuBottomMain.isShown = false}
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
                left: parent.left
                leftMargin : 10
            }
        }

        RefreshButton
        {
            id : refresh_show_button
            anchors
            {
                verticalCenter: parent.verticalCenter
                left: add_show_button_text.right
                leftMargin : 100
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
                horizontalCenter : refresh_show_button.horizontalCenter
            }
        }

        RefreshButton
        {
            id : sync_with_sickbeard_button
            anchors
            {
                verticalCenter : parent.verticalCenter
                horizontalCenter : sync_with_sickbeard_text.horizontalCenter
            }
            onClicked : {SeriesPlugin.retrieveSickBeardShows()}
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
                left : refresh_show_button_text.right
                leftMargin : 10
            }
        }
    }
}


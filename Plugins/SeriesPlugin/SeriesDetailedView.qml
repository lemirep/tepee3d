import QtQuick 2.1

Item
{
    id : serie_detailed_view
    property alias serie_title : serie_title_text.text
    property string serie_slug;
    property string serie_id;
    property alias serie_overview : serie_overview_text.text
    property alias serie_year : serie_year_text.text
    property alias serie_network : serie_network_text.text
    property alias serie_last_update : serie_last_update_text.text
    property alias serie_air_day : serie_air_day_text.text
    property alias serie_air_time : serie_air_time_text.text
    property bool  serie_on_sickbeard;

    opacity : (show_pathview_container.model.count > 0) ? 1 : 0

    Behavior on opacity {NumberAnimation {duration: 750}}

    Rectangle
    {
        color : "grey"
        opacity : 0.2
        anchors.fill: parent
        radius : 5
        border
        {
            width : 1
            color : "white"
        }
    }

    Text
    {
        id : serie_title_text
        color : "white"
        anchors
        {
            top : parent.top
            horizontalCenter : parent.horizontalCenter
            topMargin : 10
        }

        font.pixelSize: mainWindow.largeFontSize
    }

    Text
    {
        id : serie_year_text
        anchors
        {
            top : serie_title_text.bottom
            topMargin : 5
            horizontalCenter : parent.horizontalCenter
        }
        color : "white"
        font.pixelSize: mainWindow.defaultFontSize
    }
    Text
    {
        id : serie_air_day_text
        anchors
        {
            left : parent.left
            top : serie_year_text.bottom
            leftMargin : 10
            topMargin : 5
        }
        color : "white"
        font.pixelSize: mainWindow.defaultFontSize
    }
    Text
    {
        id : serie_air_time_text
        anchors
        {
            left : serie_air_day_text.right
            top : serie_air_day_text.top
            leftMargin : 10
        }
        color : "white"
        font.pixelSize: mainWindow.defaultFontSize
    }
    Text
    {
        id : serie_network_text
        anchors
        {
            left : serie_air_time_text.right
            top : serie_air_time_text.top
            leftMargin : 10
        }
        color : "white"
        font.pixelSize: mainWindow.defaultFontSize
    }
    Text
    {
        id : serie_last_update_text
        anchors
        {
            left : parent.left
            top : serie_network_text.bottom
            leftMargin : 10
            topMargin : 5
        }
        color : "white"
        font.pixelSize: mainWindow.defaultFontSize
    }

    Image
    {
        visible : serie_on_sickbeard
        height : 40
        anchors
        {
            left : parent.left
            bottom : parent.bottom
        }
        fillMode: Image.PreserveAspectFit
        source : "sickbeard_logo.png"
    }

    Flickable
    {
        clip : true
        anchors
        {
            top : serie_last_update_text.bottom
            left : parent.left
            right : parent.right
            bottom : remove_button.top
            topMargin : 15
            leftMargin : 10
            rightMargin : 10
            bottomMargin : 10
        }
        flickableDirection: Flickable.VerticalFlick
        contentWidth : parent.width - 20
        contentHeight: serie_overview_text.height
        Text
        {
            id : serie_overview_text
            width : parent.width - 20
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            color : "white"
            font.pixelSize: mainWindow.defaultFontSize
        }
    }

    CloseButton
    {
        id : remove_button
        height : 50
        anchors
        {
            bottom : parent.bottom
            right : parent.right
        }
        onClicked:
        {
            series_plugin.removeShowFromFollowedModel(serie_id)
            season_pathview_container.model = null
            episodes_pathview_container.model = null;
        }
    }
}

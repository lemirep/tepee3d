import QtQuick 2.0

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

    Rectangle
    {
        color : "grey"
        opacity : 0.2
        anchors.fill: parent
        radius : 5
    }

    Text
    {
        id : serie_title_text
        anchors
        {
            horizontalCenter : parent.horizontalCenter
            top : parent.top
            topMargin : 5
        }
        font.pointSize: 14
        color : "white"
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
        font.pointSize: 12
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
        font.pointSize: 12
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
        font.pointSize: 12
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
        font.pointSize: 12
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
        font.pointSize: 12
    }

    Flickable
    {
        clip : true
        anchors
        {
            top : serie_last_update_text.bottom
            left : parent.left
            right : parent.right
            bottom : parent.bottom
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
            font.pointSize: 12
        }
    }

    Image
    {
        visible : serie_on_sickbeard
        height : 50
        anchors
        {
            left : parent.left
            bottom : parent.bottom
        }
        fillMode: Image.PreserveAspectFit
        source : "sickbeard_logo.png"
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
            SeriesPlugin.removeShowFromFollowedModel(serie_id)
            season_pathview_container.model = null
            episodes_pathview_container.model = null;
        }
    }
}

import QtQuick 2.0

Item
{
    SerieBackground {anchors.fill: parent}

    TextInputComponent
    {
        id : sb_url_input
        placeHolder : "SickBeard Url : "
        anchors
        {
            top : parent.top
            topMargin : 20
            left : parent.left
            right : parent.right
            leftMargin : 10
            rightMargin : 10
        }
        text : SeriesPlugin.sickBeardUrl
        onAccepted : {SeriesPlugin.sickBeardUrl = sb_url_input.text}
    }
    TextInputComponent
    {
        id : sb_key_input
        placeHolder : "SickBeard API KEY : "
        anchors
        {
            top : sb_url_input.bottom
            topMargin : 20
            left : parent.left
            right : parent.right
            leftMargin : 10
            rightMargin : 10
        }
        text : SeriesPlugin.sickBeardApi
        onAccepted : {SeriesPlugin.sickBeardApi = sb_key_input.text}
    }

    OkButton
    {
        id : ok_button

        anchors
        {
            right : parent.horizontalCenter
            top : sb_key_input.bottom
            topMargin : 20
            rightMargin : 20
        }

        onClicked :
        {
            sb_url_input.accepted();
            sb_key_input.accepted();
            SeriesPlugin.saveSickBeardConfig();
            SeriesPlugin.pluginState = "shows_view";
        }
    }

    CloseButton
    {
        id : close_button
        anchors
        {
            left : parent.horizontalCenter
            top : sb_key_input.bottom
            topMargin : 20
            leftMargin : 20
        }
        onClicked :
        {
            SeriesPlugin.pluginState = "shows_view";
        }
    }
}

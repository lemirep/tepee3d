import QtQuick 2.0

Item
{
    SerieBackground {anchors.fill: parent}

    Text
    {
        id : url_label
        color : "white"
        text : "Sickbeard Url : "
        anchors
        {
            top : parent.top
            left : parent.left
            topMargin : 20
            leftMargin : 10
        }
        font.pointSize: mainWindow.largeFontSize
    }

    TextInputComponent
    {
        id : sb_url_input
        placeHolder : "URL"
        anchors
        {
            top : url_label.bottom
            topMargin : 10
            left : parent.left
            right : parent.right
            leftMargin : 10
            rightMargin : 10
        }
        text : SeriesPlugin.sickBeardUrl
        onAccepted : {SeriesPlugin.sickBeardUrl = sb_url_input.text}
    }

    Text
    {
        id : apikey_label
        color : "white"
        text : "Sickbeard API Key : "
        anchors
        {
            top : sb_url_input.bottom
            left : parent.left
            topMargin : 10
            leftMargin : 10
        }
        font.pointSize: mainWindow.largeFontSize
    }

    TextInputComponent
    {
        id : sb_key_input
        placeHolder : "API KEY"
        anchors
        {
            top : apikey_label.bottom
            topMargin : 20
            left : parent.left
            right : parent.right
            leftMargin : 10
            rightMargin : 10
        }
        text : SeriesPlugin.sickBeardApi
        onAccepted : {SeriesPlugin.sickBeardApi = sb_key_input.text}
    }

    Text
    {
        id : addshow_label
        color : "white"
        text : "Add show to Sickbeard when adding to the plugin ?"
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        width : parent.width - (20 + add_show_sickbeard.width + 10)
        anchors
        {
            top : sb_key_input.bottom
            left : parent.left
            right : add_show_sickbeard
            topMargin : 10
            leftMargin : 10
        }
        font.pointSize: mainWindow.defaultFontSize
    }

    CheckBox
    {
        id : add_show_sickbeard
        checked : SeriesPlugin.addToSickBeard
        onToggle :
        {
            console.log("Checked Changed " + checked);
             SeriesPlugin.addToSickBeard = checked
        }
        anchors
        {
            top : addshow_label.top
            right : parent.right
            rightMargin : 10
        }
        width : 50
    }

    OkButton
    {
        id : ok_button

        anchors
        {
            right : parent.horizontalCenter
            top : add_show_sickbeard.bottom
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
            top : add_show_sickbeard.bottom
            topMargin : 20
            leftMargin : 20
        }
        onClicked :
        {
            SeriesPlugin.pluginState = "shows_view";
        }
    }
}

import QtQuick 2.1

Item
{
    anchors.fill: parent

    Row
    {
        anchors
        {
           horizontalCenter : parent.horizontalCenter
            bottom : parent.bottom
            top : parent.top
            topMargin : 50
        }
        spacing: 50

        Flickable
        {
            width : 220
            height: parent.height
            boundsBehavior: Flickable.StopAtBounds
            contentHeight: xbmc_auth.height

            Column
            {
                id : xbmc_auth
                width : parent.width
                Column
                {
                    Text {text : "Url"; color : "white"; font.pixelSize: mainWindow.defaultFontSize}
                    TextInputComponent {id : url_input; width : xbmc_auth.width; text : xbmc_plugin.xbmcServerUrl}
                }
                Column
                {
                    Text {text : "Port"; color : "white"; font.pixelSize: mainWindow.defaultFontSize}
                    TextInputComponent {id : port_input; width : xbmc_auth.width; text : xbmc_plugin.xbmcServerPort}
                }
                Column
                {
                    Text {text : "Username"; color : "white"; font.pixelSize: mainWindow.defaultFontSize}
                    TextInputComponent {id : username_input; width : xbmc_auth.width; text : xbmc_plugin.xbmcServerUserName}
                }
                Column
                {
                    Text {text : "Password"; color : "white"; font.pixelSize: mainWindow.defaultFontSize}
                    TextInputComponent {id : password_input; width : xbmc_auth.width; text : xbmc_plugin.xbmcServerPassword}
                }
                OkButton
                {
                    width : 50
                    anchors.horizontalCenter: parent.horizontalCenter
                    onClicked :
                    {
                        xbmc_plugin.xbmcServerUrl = url_input.text
                        xbmc_plugin.xbmcServerPort = port_input.text
                        xbmc_plugin.xbmcServerUserName = username_input.text
                        xbmc_plugin.xbmcServerPassword = password_input.text
                        xbmc_plugin.saveXBMCAuthToDatabase()
                    }
                }
            }
        }

        Item
        {
            width : refresh_libraries_text.width
            height : parent.height
            RefreshButton
            {
                id : refresh_libraries
                anchors
                {
                    bottom : parent.verticalCenter
                    horizontalCenter : refresh_libraries_text.horizontalCenter
                }
                onClicked :
                {
                    xbmc_plugin.refreshLibraries();
                }
            }
            Text
            {
                id : refresh_libraries_text
                color : "white"
                font.pixelSize: mainWindow.defaultFontSize
                text : "Refresh Media Libraries"
                anchors
                {
                    top : refresh_libraries.bottom
                    topMargin : 25
                }
            }
        }
    }
}

import QtQuick 2.0

Item
{
    anchors.fill: parent


    Flickable
    {
        width : 220
        anchors
        {
            left : parent.left
            leftMargin : 50
            bottom : parent.bottom
            top : parent.top
            topMargin : 25
        }
        boundsBehavior: Flickable.StopAtBounds
        contentHeight: xbmc_auth.height

        Column
        {
            id : xbmc_auth
            width : parent.width
            Column
            {
                Text {text : "Url"; color : "white"; font.pixelSize: mainWindow.defaultFontSize}
                TextInputComponent {id : url_input; width : xbmc_auth.width; text : XBMCPlugin.xbmcServerUrl}
            }
            Column
            {
                Text {text : "Port"; color : "white"; font.pixelSize: mainWindow.defaultFontSize}
                TextInputComponent {id : port_input; width : xbmc_auth.width; text : XBMCPlugin.xbmcServerPort}
            }
            Column
            {
                Text {text : "Username"; color : "white"; font.pixelSize: mainWindow.defaultFontSize}
                TextInputComponent {id : username_input; width : xbmc_auth.width; text : XBMCPlugin.xbmcServerUserName}
            }
            Column
            {
                Text {text : "Password"; color : "white"; font.pixelSize: mainWindow.defaultFontSize}
                TextInputComponent {id : password_input; width : xbmc_auth.width; text : XBMCPlugin.xbmcServerPassword}
            }
            OkButton
            {
                width : 50
                anchors.left: parent.left
                onClicked :
                {
                    XBMCPlugin.xbmcServerUrl = url_input.text
                    XBMCPlugin.xbmcServerPort = port_input.text
                    XBMCPlugin.xbmcServerUserName = username_input.text
                    XBMCPlugin.xbmcServerPassword = password_input.text
                    XBMCPlugin.saveXBMCAuthToDatabase()
                }
            }
        }
    }
}

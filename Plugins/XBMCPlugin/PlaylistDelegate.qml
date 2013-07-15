import QtQuick 2.0

Item
{
    property alias itemModel : playlist_listview.model
    property string stringType;
    property int idPlaylist;

    Image
    {
        id : playlist_img
        height: 50
        fillMode: Image.PreserveAspectFit
        source : (stringType == "audio") ? "music.png" : "shows.png"
        anchors
        {
            top : parent.top
            right : parent.right
        }
    }

    // PLAY BUTTON
    Image
    {
        id : play_playlist_buttom
        height : 50
        fillMode: Image.PreserveAspectFit
        scale : play_playlist_ma.pressed ? 0.9 : 1
        source : "small_play.png"
        MouseArea
        {
            id : play_playlist_ma
            anchors.fill: parent
            onClicked: XBMCPlugin.playPlaylist(idPlaylist, 0)
        }
        anchors
        {
            verticalCenter : parent.verticalCenter
            right : parent.right
        }
    }

    // CLEAR BUTTON
    CloseButton
    {
        height : parent.height / 4
        onClicked : XBMCPlugin.clearPlaylist(idPlaylist)
        anchors
        {
            bottom : parent.bottom
            right : parent.right
        }
    }

    ListView
    {
        id : playlist_listview
        clip : true
        spacing: 5
        anchors
        {
            left : parent.left
            right : playlist_img.left
            bottom : parent.bottom
            top : parent.top
            leftMargin : 20
            rightMargin : 20
            topMargin : 5
            bottomMargin : 5
        }
        delegate : Component {
            Item
            {
                width : playlist_listview.width
                height : playlist_listview.height / 10
                Rectangle
                {
                    height: 1
                    anchors
                    {
                        bottom: parent.bottom
                        horizontalCenter : parent.horizontalCenter
                    }
                    width : parent.width / 4
                    color : "lightgrey"
                }
                Text
                {
                    anchors.fill: parent
                    color : "white"
                    text : model.title
                    font.pixelSize: mainWindow.largeFontSize
                    clip : true
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                MouseArea
                {
                    anchors.fill: parent
                    onClicked: XBMCPlugin.playPlaylist(idPlaylist, index)
                }
            }
        }
    }
}

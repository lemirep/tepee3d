import QtQuick 2.0

Item
{
    property alias itemModel : playlist_listview.model
    property string stringType;
    property int idPlaylist;

    Image
    {
        id : playlist_img
        height: parent.height / 4
        fillMode: Image.PreserveAspectFit
        source : (stringType == "audio") ? "music.png" : "shows.png"
        anchors
        {
            top : parent.top
            right : parent.right
        }
    }

    // PLAY BUTTON

    // CLEAR BUTTON

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
                height : playlist_listview.height / 3
                Rectangle
                {
                    anchors.fill: parent
                    color : "transparent"
                    radius : 2
                    border
                    {
                        width : 1
                        color : "white"
                    }
                    opacity : 0.2
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
            }
        }
    }
}

import QtQuick 2.0
import QtGraphicalEffects 1.0

Item
{
    anchors.fill: parent
    GridView
    {
        id : artists_library_gridview
        anchors.fill: parent
        model : XBMCPlugin.getArtistsLibrary();
        cellWidth : width / 5
        cellHeight : cellWidth
        delegate : Component {
            Item
            {
                width : artists_library_gridview.cellWidth
                height : artists_library_gridview.cellHeight
                Image
                {
                    id : artist_image
                    height : parent.height - 30
                    anchors
                    {
                        topMargin : 5
                        horizontalCenter: parent.horizontalCenter
                        top: parent.top
                    }
                    asynchronous : true
                    fillMode: Image.PreserveAspectFit
                    source : XBMCPlugin.getXBMCImageProviderUrl(model.thumbnail)
                    Behavior on scale {NumberAnimation {duration : 1200; easing.type: Easing.InOutBack}}
                    scale : (status == Image.Ready) ? 1 : 0
                    onStatusChanged: {if (status == Image.Error) source = "empty_cd.png"}
                }
                Image
                {
                    id : cd_cover
                    source : "cdbox.png"
                    anchors
                    {
                        left : artist_image.left
                        leftMargin : -21
                        right : artist_image.right
                        rightMargin : -5
                        top : artist_image.top
                        topMargin : -8
                        bottom : artist_image.bottom
                        bottomMargin : -6
                    }
                     scale : artist_image.scale
                }
                Text
                {
                    id : title_text
                    text : model.artistName
                    width : parent.width
                    color : "white"
                    font.pixelSize: mainWindow.defaultFontSize
                    horizontalAlignment: Text.AlignHCenter
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                    clip : true
                    anchors
                    {
                        bottom : parent.bottom
                        bottomMargin : 8
                    }
                }
            }
        }
    }
}

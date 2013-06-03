import QtQuick 2.0

Item
{
    anchors.fill: parent
    GridView
    {
        id : albums_library_gridview
        anchors.fill: parent
        model : XBMCPlugin.getAlbumsLibrary();
        cellWidth : width / 5
        cellHeight : cellWidth
        delegate : Component {
            Item
            {
                width : albums_library_gridview.cellWidth
                height : albums_library_gridview.cellHeight

                Image
                {
                    id : album_image
                    height : parent.height - 40
                    anchors
                    {
                        topMargin : 5
                        horizontalCenter: parent.horizontalCenter
                        top: parent.top
                    }
                    asynchronous : true
                    fillMode: Image.PreserveAspectFit
                    source : XBMCPlugin.getXBMCImageProviderUrl(model.thumbnail)
                    onStatusChanged: {if (status == Image.Error) source = "empty_cd.png"}
                    Behavior on scale {NumberAnimation {duration : 1200; easing.type: Easing.InOutBack}}
                    scale : (status == Image.Ready) ? 1 : 0
                }
                Image
                {
                    id : cd_cover
                    source : "cdbox.png"
                    anchors
                    {
                        left : album_image.left
                        leftMargin : -21
                        right : album_image.right
                        rightMargin : -5
                        top : album_image.top
                        topMargin : -8
                        bottom : album_image.bottom
                        bottomMargin : -6
                    }
                     scale : album_image.scale
                }
                Text
                {
                    id : title_text
                    text : model.albumTitle
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
